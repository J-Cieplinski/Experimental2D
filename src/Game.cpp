#include "Game.hpp"
#include "states/GameState.hpp"
#include "../dependencies/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;


void Game::initStates() {
    m_states.push(std::move(std::make_unique<GameState>(m_window)));
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
    while(!m_states.empty()) {
        m_states.pop();
    }
}

void Game::update() {
    updateEvents();
    if(!m_states.empty()) {
        auto currentState = m_states.top().get();
        currentState->update(m_dt);

        if(currentState->isQuitting()) {
            currentState->exitState();
            m_states.pop();
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

    if(!m_states.empty()) {
        m_states.top()->render();
    }

    m_window->display();
}
