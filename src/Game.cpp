#include "Game.hpp"
#include "../dependencies/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void Game::run() {
    while(m_window->isOpen()) {
        update();
        render();
    }
}

Game::Game()
{
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

void Game::update() {
    while (m_window->pollEvent(m_event))
    {
        if(m_event.type == sf::Event::Closed) {
            m_window->close();
        }
    }

}

void Game::render() {
    m_window->clear();
    m_window->display();
}
