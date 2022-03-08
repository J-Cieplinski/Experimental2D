#pragma once
#include "SFML/Graphics.hpp"
#include "states/State.hpp"
#include "util.hpp"

class Observer {
    public:
        Observer(State& state) : state_(state) {};
        virtual ~Observer() {
            state_.removeObserver(this);
        };
        Observer(const Observer& copyFrom) = default;
        Observer& operator=(const Observer& copyFrom) = default;
        Observer(Observer&& moveFrom) = default;
        Observer& operator=(Observer&& moveFrom) = default;
        virtual void onNotify(Event event, State& state) = 0;
    private:
        State& state_;
};
