#include "State.hpp"
#include "../entities/Entity.hpp"
class GameState : public State {
    public:
        GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
    private:
        Entity player_;

        void initPlayer();
};