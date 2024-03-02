#pragma once

#include "SFML/Graphics.hpp"
#include <map>

class TextureRect {
    public:
        TextureRect();
        TextureRect(int x, int y, int width, int height);

        sf::Sprite sprite;

        static sf::Texture spriteSheet;
        static TextureRect *types;

        static const float SCALE_FACTOR;

        enum TYPES {
            GRASS,
            SAND
        };

        static void initializeTypes() {
            spriteSheet.loadFromFile("assets/tiles.png");
            delete types;

            TextureRect t[] = {
                TextureRect(0, 0, 16, 16),
                TextureRect(16, 0, 16, 16)
            };

            types = new TextureRect[sizeof(t) / sizeof(TextureRect)];
            for (int i = 0; i < (int)(sizeof(t) / sizeof(TextureRect)); i++) {
                types[i] = t[i];
            }
        };

        int x, y;
        int width, height;
};