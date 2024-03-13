#pragma once

#include "SFML/Graphics.hpp"

class Effect {
    public:
        float damage;
        int ticks;
        sf::Vector2f force;
        bool isAberrating;

        Effect() {};
        Effect(float damage, int ticks, sf::Vector2f force) : 
        damage(damage), ticks(ticks), force(force), isAberrating(false) {};
        Effect(float damage, int ticks, sf::Vector2f force, bool isAberrating) : 
        damage(damage), ticks(ticks), force(force), isAberrating(isAberrating) {};
};