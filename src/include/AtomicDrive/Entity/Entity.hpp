#pragma once

#include "SFML/Graphics.hpp"
#include "EntityController.hpp"
#include "AtomicDrive/World/Tile.hpp"

class Entity {
    public:
        ENTITY_CONTROLLER controller;

        float x, y;
        //std::vector<Effect> effects;
        sf::Vector2f acceleration, velocity;
        sf::Vector2f momentum;

        /*
        void update() {
            controller->update(this);
        }

        void draw(sf::RenderTexture *r) {
            controller->draw(this, r);
        }

        void affect(Effect effect) {
            controller->affect(this, effect);
        }
        */
        
        int *ivars;
        float *fvars;
};