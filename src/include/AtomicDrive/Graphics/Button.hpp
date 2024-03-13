#pragma once

#include "TextureRect.cpp"
#include "SFML/Graphics.hpp"

class Button {
    public:
    enum BUTTON_TYPE {
        LABEL,
        HEALTH,
        AMMO,
        SCREWS,
        ABER_RECHARGE
    };

    class TextPos {
        public:
        std::string text;
        int x, y;

        TextPos(std::string text, int x, int y) : text(text), x(x), y(y) {};
        TextPos() {};
    };

    static sf::Font font;

    BUTTON_TYPE type;

    int x, y;
    int width, height;
    bool hasBeenClicked;
    bool visible;
    bool drawTexture = true;
    //sf::RenderTexture buffer;
    std::vector<TextPos> text;
    TextureRect *texture;

    bool checkClick(int mouseX, int mouseY) {
        return !(mouseX > x + width
            ||   mouseX < x
            ||   mouseY > y + height
            ||   mouseY < y);
    }

    void click(int mouseX, int mouseY) {
        hasBeenClicked = checkClick(mouseX, mouseY);
    }

    void draw(sf::RenderTexture &r) {
        if (drawTexture) {
            texture->sprite.setPosition(x, y);
            r.draw(texture->sprite);
        }
        sf::Text t;
        t.setCharacterSize(8);
        for (TextPos &tp : text) {
            t.setFont(font);
            t.setPosition(x + tp.x, y + tp.y);
            t.setFillColor(sf::Color::White);
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

    Button(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        visible = true;
        drawTexture = false;
        hasBeenClicked = false;
    };

    static void initialize() {
        font.loadFromFile("assets/Roboto-Bold.ttf");
    }
};