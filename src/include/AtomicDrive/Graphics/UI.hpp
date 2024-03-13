#pragma once

#include "Button.cpp"

class UI {
    public:
        enum SCENES {
            MAIN_GAME,
            MAIN_MENU,
            WORKSHOP,
            INTRO_1,
            INTRO_2,
            INTRO_3,
            INTRO_4,
            ANY
        };

        std::vector<Button> buttons;
        int scene = 0;

        void draw(sf::RenderTexture &r) {
            for (Button &b : buttons) {
                b.draw(r);
            }
        }

        void update(sf::Window &w) {
            sf::Event e;
            for (Button &b : buttons) {
                b.hasBeenClicked = false;
            }
            while (w.pollEvent(e)) {
                if (e.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(w);
                    for (Button &b : buttons) {
                        b.click(mousePos.x/TextureRect::SCALE_FACTOR, mousePos.y/TextureRect::SCALE_FACTOR);
                    }
                }
            }
        }

        UI() {
            Button::initialize();
        }
};