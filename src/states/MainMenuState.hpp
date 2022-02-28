#include "State.hpp"

class MainMenuState : public State {
        public:
        MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
};