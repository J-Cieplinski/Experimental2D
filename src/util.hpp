#pragma once
#include <cmath>
#include <sstream>

enum class States {
    GAME,
    PAUSED,
    MENU,
    SETTINGS,
    EDITOR
};

enum class Event {
    MOUSE_LEFT_CLICK,
    MOUSE_RIGHT_CLICK
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
    BACKGROUND = 0,
    BACKGROUND_DECALS = 1,
    ENTITY = 2,
    FOREGROUND = 3,
    FOREGROUND_DECALS = 4,
    MAX_LAYERS
};

enum class Textures {
    PLAYER,
    BACKGROUND,
    MAP,
    PLACEHOLDER
};

enum class Fonts {
    MAIN
};

inline bool operator<(MapLayer left, MapLayer right) {
    return static_cast<std::underlying_type_t<MapLayer>>(left) < static_cast<std::underlying_type_t<MapLayer>>(right);
};

inline std::string operator<<(const std::string& left, Textures right) {
    std::stringstream ss;
    ss << left;
    switch(right) {
        case Textures::PLAYER:
            ss << "Textures::PLAYER";
            break;
        case Textures::BACKGROUND:
            ss << "Textures::BACKGROUND";
            break;
        case Textures::MAP:
            ss << "Textures::MAP";
            break;
        case Textures::PLACEHOLDER:
            ss << "Textures::PLACEHOLDER";
            break;
    }

    return ss.str();
};

inline std::string operator<<(const std::string& left, Fonts right) {
    std::stringstream ss;
    ss << left;
    switch(right) {
        case Fonts::MAIN:
            ss << "Fonts::MAIN";
            break;
    }

    return ss.str();
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