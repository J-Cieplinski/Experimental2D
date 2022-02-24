#include "Game.hpp"
#include "states/GameState.hpp"
#include "../dependencies/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Game::initStates() {
    m_states[States::GAME] = std::make_unique<GameState>(m_window, this);
    m_currentState = m_states[States::GAME].get();
}

void Game::initWindow() {
    std::ifstream configFile("configs\\window.json");
    auto config = json::parse(configFile);
    configFile.close();
    auto windowConfig = config["window"];

    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowConfig["width"], windowConfig["height"]), windowConfig["title"]);
    if(windowConfig["VSync"]["enabled"]) {
        m_window->setVerticalSyncEnabled(true);
        m_window->setFramerateLimit(windowConfig["VSync"]["FPScap"]);
    }
}

void Game::run() {
    while(m_window->isOpen()) {
        updateDt();
        update();
        render();
    }
}

Game::Game() {
    initWindow();
    initStates();
}

Game::~Game() {
    m_states.clear();
}

void Game::changeState(States stateId, std::unique_ptr<State> state) {
    // cleanup the current state
	if (!m_states.empty()) {
        m_currentState->cleanup();
        auto it = std::find_if(m_states.begin(), m_states.end(), [&](const auto& el) {
            return el.second.get() == m_currentState;
        });
        m_states.erase(it);
        m_currentState = nullptr;
	}

    if(!m_states[stateId]) {
        m_states[stateId] = std::move(state);
    }

    m_currentState = m_states[stateId].get();
    m_currentState->unpause();
}

void Game::pushState(States stateId, std::unique_ptr<State> state) {
    // pause current state
	if (m_currentState) {
		m_currentState->pause();
	}

	// store and init the new state
    if(!m_states[stateId]) {
        m_states[stateId] = std::move(state);
    }

    m_currentState = m_states[stateId].get();
    m_currentState->unpause();
}

void Game::update() {
    updateEvents();
    if(m_currentState) {
        m_currentState->update(m_dt);
        if(m_currentState->isQuitting()) {
            m_window->close();
        }
    }
}

void Game::updateEvents() {
    while (m_window->pollEvent(m_event))
    {
        if(m_event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

void Game::updateDt() {
    m_dt = m_dtClock.restart().asSeconds();
}

void Game::render() {
    m_window->clear();

    if(m_currentState) {
        m_currentState->render();
    }

    m_window->display();
}
