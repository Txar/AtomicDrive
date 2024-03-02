#pragma once

#include "SFML/Graphics.hpp"

class Effect {
    public:
        sf::Vector2f force;
        float damage;
        int ticks;
};