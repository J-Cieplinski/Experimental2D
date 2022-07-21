#include "State.hpp"

namespace gui {
    class Button;
}

class EditorState : public State {
    public:
        EditorState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
    private:
        std::vector<gui::Button> buttons_;
};