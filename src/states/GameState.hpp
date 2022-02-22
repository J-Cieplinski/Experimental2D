#include "State.hpp"

class GameState : public State {
    public:
        GameState(std::shared_ptr<sf::RenderWindow> targetWindow);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void exitState() override;
};