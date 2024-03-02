#include "AtomicDrive.hpp"

AtomicDrive::AtomicDrive() : world() {
    window.create(sf::VideoMode(1200, 720), "Atomic Drive");
    terrainBuffer.create(1200, 720);
    window.setFramerateLimit(60);
    TextureRect::initializeTypes();
    world = World(2, 2);
    world.renderChunks();
    
    Entity playerEntity;
    playerEntity.x = 0;
    playerEntity.y = 0;
    playerEntity.acceleration = sf::Vector2f(0.0, 0.0);
    playerEntity.velocity = sf::Vector2f(0.0, 0.0);
    playerEntity.controller = ENTITY_CONTROLLER::PLAYER;
    world.entities.push_back(playerEntity);
}

void AtomicDrive::update() {
    if (player) {
        camera.x = (int)player->x;
        camera.y = (int)player->y;
    }
    else {
        camera = sf::Vector2i(0.0, 0.0);
    }
    world.update();

    for (Entity &e : world.entities) {
        switch (e.controller) {
            case ENTITY_CONTROLLER::PLAYER: {
                if (!player) {
                    player = &e;
                    e.velocity = sf::Vector2f(0.0, 0.0);
                    e.x = 16;
                    e.y = 16;
                }

                e.acceleration = sf::Vector2f(0.0, 0.0);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    e.acceleration += sf::Vector2f(0.1, 0.0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    e.acceleration += sf::Vector2f(-0.1, 0.0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    e.acceleration += sf::Vector2f(0.0, 0.1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    e.acceleration += sf::Vector2f(0.0, -0.1);
                }

                e.velocity += e.acceleration;

                if (e.velocity.x >  4) e.velocity.x =  4;
                if (e.velocity.y >  4) e.velocity.y =  4;
                if (e.velocity.x < -4) e.velocity.x = -4;
                if (e.velocity.y < -4) e.velocity.y = -4;
                e.x += e.velocity.x;
                e.y += e.velocity.y;

                break;
            }
            default:
                break;
        }
    }
}

void AtomicDrive::draw() {
    window.clear({0, 0, 0});
    terrainBuffer.clear({0, 0, 0});
    world.draw(&terrainBuffer, camera);
    terrainBuffer.display();
    sf::Sprite s(terrainBuffer.getTexture());
    s.setScale(TextureRect::SCALE_FACTOR, TextureRect::SCALE_FACTOR);
    window.draw(s);
    window.display();
}

void AtomicDrive::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::Escape):
                    window.close();
                    break;
                default:
                    break;
            }
        }
    }
}

int AtomicDrive::mainLoop() {
    bool running = true;
    while (running) {
        pollEvents();
        update();
        draw();
        running = window.isOpen();
    }

    return 0;
}