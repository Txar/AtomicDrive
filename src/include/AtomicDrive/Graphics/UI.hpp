#pragma once

#include "Button.cpp"

class UI {
    public:
        std::vector<Button> buttons;

        void draw(sf::RenderTexture &r) {
            for (Button &b : buttons) {

            }
        }

        UI() {}
};