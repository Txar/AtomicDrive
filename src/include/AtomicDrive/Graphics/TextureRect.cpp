#include "TextureRect.hpp"
#include <iostream>

sf::Texture TextureRect::spriteSheet = sf::Texture();
TextureRect *TextureRect::types = new TextureRect();

TextureRect::TextureRect() {}

const float TextureRect::SCALE_FACTOR = 3.0;

TextureRect::TextureRect(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    sprite.setTexture(spriteSheet);
    sprite.setTextureRect({x, y, width, height});
}