#pragma once

#include "SFML/Graphics.hpp"
#include "EntityController.hpp"
#include "EntityRenderer.hpp"
#include "AtomicDrive/World/Tile.hpp"
#include "Effect.cpp"
#include "Collider.cpp"
#include "AtomicDrive/SoundManager.cpp"
#include "SFML/Audio.hpp"

class Entity {
    public:
        ENTITY_CONTROLLER controller;
        ENTITY_RENDERER renderer;

        static int incrementId;

        int id;
        float x, y;
        float mass;
        float rotation; //DEGREES!!
        float frictionCoefficient;
        float acceleration;
        float maxHealth;
        float health;

        bool isDead = false;
        TextureRect *sprite;
        std::vector<Effect> effects;
        
        sf::Vector2f velocity;
        sf::Vector2f momentum;

        std::vector<Collider> colliders;
        SoundManager soundManager;

        Entity();

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