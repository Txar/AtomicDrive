#pragma once

#include "World/World.cpp"
#include "Graphics/UI.hpp"

class AtomicDrive {
    public:
        AtomicDrive();

        int mainLoop();
        void update();
        void draw();
        void pollEvents();

        int fps;
        int frame;
        UI ui;

        int screwsOwned = 0;
        int screenShakeFrames = 0;

        void drawUI();
        void updateUI();
        void AffectEntity(Entity &e, Effect effect);
        void calculateCarPhysics(Entity &e, float turning, sf::Vector2f acceleration, bool goingBack, World &world);
        Collider::CollisionType checkCarCollisions(Entity &e, World &world);
        
        Entity *player;
        sf::Vector2i camera;
        sf::RenderTexture worldBuffer;
        sf::Vector2i renderResolution;
        sf::RenderWindow window;
        SoundManager soundManager;
        World world;
};