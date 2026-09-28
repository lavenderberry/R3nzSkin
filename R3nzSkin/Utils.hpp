#pragma once

#include <concepts>
#include <mutex>
#include <random>
#include <string>

#include "imgui/imgui.h"

class RandomGenerator {
public:
    template <std::integral T>
    [[nodiscard]] static T random(T min, T max) noexcept
    {
        std::scoped_lock lock{ mutex };
        return std::uniform_int_distribution{ min, max }(gen);
    }
private:
    inline static std::mt19937 gen{ std::random_device{}() };
    inline static std::mutex mutex;
};

template <typename T>
[[nodiscard]] T random(T min, T max) noexcept
{
    return RandomGenerator::random(min, max);
}

class KeyBind {
public:
    enum KeyCode : unsigned char {
        APOSTROPHE = 0, COMMA, MINUS, PERIOD, SLASH, KEY_0, KEY_1, KEY_2,
        KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, SEMICOLON, EQUALS,
        A, ADD, B, BACKSPACE, C, CAPSLOCK, D, DECIMAL, DEL, DIVIDE, DOWN, E,
        END, ENTER, F, F1, F10, F11, F12, F2, F3, F4, F5, F6, F7, F8, F9, G,
        H, HOME, I, INSERT, J, K, L, LALT, LCTRL, LEFT, LSHIFT, M, MOUSE1, MOUSE2,
        MOUSE3, MOUSE4, MOUSE5, MULTIPLY, MOUSEWHEEL_DOWN, MOUSEWHEEL_UP, N, NONE,
        NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7,
        NUMPAD_8, NUMPAD_9, O, P, PAGE_DOWN, PAGE_UP, Q, R, RALT, RCTRL, RIGHT, RSHIFT,
        S, SPACE, SUBTRACT, T, TAB, U, UP, V, W, X, Y, Z, LEFTBRACKET, BACKSLASH,
        RIGHTBRACKET, BACKTICK, MAX
    };

    KeyBind() = default;
    explicit KeyBind(KeyCode keyCode) noexcept;
    explicit KeyBind(const char* keyName) noexcept;

    bool operator==(KeyCode keyCode) const noexcept { return this->keyCode == keyCode; }
    friend bool operator==(const KeyBind& a, const KeyBind& b) noexcept { return a.keyCode == b.keyCode; }

    const char* toString() const noexcept;
    int getKey() const noexcept;

    bool setToPressedKey() noexcept;
private:
    KeyCode keyCode{ KeyCode::NONE };
};

namespace ImGui
{
    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* userData = nullptr) noexcept;
	void textUnformattedCentered(const char* text) noexcept;
	void rainbowText() noexcept;
    void hotkey(const char* label, KeyBind& key, float samelineOffset = 0.0f, const ImVec2& size = { 100.0f, 0.0f }) noexcept;
    void hoverInfo(const char* desc) noexcept;
};
