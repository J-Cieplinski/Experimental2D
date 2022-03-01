#pragma once
#include <cmath>

enum class States {
    GAME = 1,
    PAUSED = 2,
    MENU = 3
};

enum class Event {
    MOUSE_CLICK = 1
};

// Linear interpolation function. Works for vectors
template <typename T, typename U>
T lerp(T start, T end, U t) {
    return static_cast<T>(start * t + end * (1 - t));
}

template <typename T>
auto length(T vector) {
    return std::hypot(vector.x, vector.y);
}

template <typename T>
T normalize(T vector) {
    auto len = length(vector);
    return T(vector.x / len, vector.y / len);
}