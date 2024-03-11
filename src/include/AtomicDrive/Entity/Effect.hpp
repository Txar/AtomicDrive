#pragma once

#include "SFML/Graphics.hpp"

class Effect {
    public:
        float damage;
        int ticks;
        sf::Vector2f force;

        Effect() {};
        Effect(float damage, int ticks, sf::Vector2f force) : damage(damage), ticks(ticks), force(force) {};
};