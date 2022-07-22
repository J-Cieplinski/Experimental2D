#pragma once
#include <cmath>

enum class States {
    GAME,
    PAUSED,
    MENU,
    SETTINGS,
    EDITOR
};

enum class Event {
    MOUSE_CLICK
};

enum class EntityState {
    MOVING_RIGHT,
    MOVING_LEFT,
    MOVING_UP,
    MOVING_DOWN,
    IDLE,
    ATTACKING
};

enum class MapLayer {
    BACKGROUND,
    ENTITY,
    FOREGROUND
};

inline bool operator<(MapLayer left, MapLayer right) {
    return static_cast<int>(left) < static_cast<int>(right);
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