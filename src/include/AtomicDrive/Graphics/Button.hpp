#pragma once

#include "TextureRect.cpp"
#include "SFML/Graphics.hpp"

class Button {
    public:

    class TextPos {
        public:
        std::string text;
        int x, y;

        TextPos(std::string text, int x, int y) : text(text), x(x), y(y) {};
        TextPos() {};
    };

    static sf::Font font;

    int x, y;
    int width, height;
    bool hasBeenClicked;
    bool visible;
    bool drawTexture;
    //sf::RenderTexture buffer;
    std::vector<TextPos> text;
    TextureRect *texture;

    bool checkClick(int mouseX, int mouseY) {
        return !(mouseX > x + width
            ||   mouseX < x
            ||   mouseY > y + height
            ||   mouseY < y);
    }

    void draw(sf::RenderTexture &r) {
        texture->sprite.setPosition(x, y);
        r.draw(texture->sprite);
        sf::Text t;
        t.setCharacterSize(5);
        for (TextPos &tp : text) {
            t.setFont(font);
            t.setPosition(tp.x, tp.y);
            t.setString(tp.text);
            r.draw(t);
        }
    }

    Button() {}
    Button(int x, int y, int width, int height, TextureRect *texture) : x(x), y(y), width(width), height(height), texture(texture) {
        visible = true;
        drawTexture = true;
        hasBeenClicked = false;
    };

    static void initialize() {
        font.loadFromFile("assets/Roboto-Regular.ttf");
    }
};