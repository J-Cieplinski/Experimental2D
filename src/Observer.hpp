#pragma once
#include "states/State.hpp"
#include "util.hpp"


class Observer {
    public:
        Observer(State& state) : state_(state) {}
        virtual ~Observer() {
            state_.removeObserver(this);
        }
        Observer(const Observer& copyFrom) = default;
        Observer(Observer&& moveFrom) = default;
        virtual bool onNotify(Event event, const State& state) = 0;
    private:
        State& state_;
};
