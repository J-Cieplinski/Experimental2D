#include "State.hpp"

class MainMenuState : public State {
        public:
        MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;

        private:
        std::vector<gui::Button> buttons_;
        std::unique_ptr<sf::Font> font_;

        void initButtons();
};