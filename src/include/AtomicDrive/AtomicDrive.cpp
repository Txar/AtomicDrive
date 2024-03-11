#include "AtomicDrive.hpp"
#include <math.h>

void AtomicDrive::drawUI() {
    
}

void AtomicDrive::AffectEntity(Entity &e, Effect effect) {
    e.effects.push_back(effect);
}

Collider::CollisionType AtomicDrive::checkCarCollisions(Entity &e, World &world) {
    int x = e.x / 16;
    int y = e.y / 16;

    Collider::CollisionType collision = Collider::NONE;
    for (int i = std::max(x - 5, 0); i < std::min(x + 5, Chunk::CHUNK_SIZE*world.width); i++) {
        for (int j = std::max(y - 5, 0); j < std::min(y + 5, Chunk::CHUNK_SIZE*world.height); j++) {
            for (Collider &ec : e.colliders) {
                sf::Vector2i p = Math::iRotateAroundOrigin(ec.x + ec.width/2, ec.y + ec.height/2, e.rotation*Math::DEG_TO_RAD);
                Collider c(e.x + p.x - ec.width/2, e.y + p.y - ec.height/2, ec.width, ec.height);
                if (world.cAt(i, j).collide(c)) {
                    collision = Collider::CollisionType::SOLID;
                    break;
                }
            }
            if (collision != Collider::NONE) break;
        }
        if (collision != Collider::NONE) break;
    }

    for (Entity &en : world.entities) {
        if (en.id == e.id) continue;
        for (Collider &ec : e.colliders) {
            sf::Vector2i p = Math::iRotateAroundOrigin(ec.x + ec.width/2, ec.y + ec.height/2, e.rotation*Math::DEG_TO_RAD);
            Collider c(e.x + p.x - ec.width/2, e.y + p.y - ec.height/2, ec.width, ec.height);

            for (Collider &ec2 : en.colliders) {
                sf::Vector2i p = Math::iRotateAroundOrigin(ec2.x + ec2.width/2, ec2.y + ec2.height/2, en.rotation*Math::DEG_TO_RAD);
                Collider c2(en.x + p.x - ec.width/2, en.y + p.y - ec.height/2, ec.width, ec.height);
                if (c2.collide(c)) {
                    AffectEntity(en, Effect(0, 0, sf::Vector2f(e.velocity.x/2, e.velocity.y/2)));
                    collision = Collider::CollisionType::CAR_ENTITY;
                    if (abs(e.velocity.x) + abs(e.velocity.y) > 1) {
                        float volume = (abs(e.velocity.x) + abs(e.velocity.y)) / 4.0; // 1.5;
                        volume = volume*volume;
                        e.soundManager.playSound(soundManager.car_crash, volume, e.x, e.y);
                    }
                    break;
                }
            }
            if (collision != Collider::NONE) break;
        }
        if (collision != Collider::NONE) break;
    }

    return collision;
}

void AtomicDrive::calculateCarPhysics(Entity &e, float turning, sf::Vector2f acceleration, bool goingBack, World &world) {
    int prevX = e.x;
    int prevY = e.y;
    float prevRotation = e.rotation;

    e.velocity += acceleration;

    e.velocity.x -= e.frictionCoefficient*e.velocity.x;
    e.velocity.y -= e.frictionCoefficient*e.velocity.y;

    float maxSpeed = 6;
    if (e.controller == ENTITY_CONTROLLER::AI_CAR) maxSpeed = 8.0;

    if (e.velocity.x >  maxSpeed) e.velocity.x =  maxSpeed;
    if (e.velocity.y >  maxSpeed) e.velocity.y =  maxSpeed;
    if (e.velocity.x < -maxSpeed) e.velocity.x = -maxSpeed;
    if (e.velocity.y < -maxSpeed) e.velocity.y = -maxSpeed;
    e.x += e.velocity.x;
    e.y += e.velocity.y;

    float speed = sqrt(e.velocity.x*e.velocity.x + e.velocity.y*e.velocity.y);
    //float volume = speed/maxSpeed;
    //std::cout << speed << std::endl;
    //soundManager.playSound(soundManager.engine_1, volume);
    float angleChange;

    if (goingBack) {
        angleChange = 0.07 * turning * (speed/maxSpeed);
    }
    else {
        angleChange = 0.1 * turning * (speed/maxSpeed);
    }

    e.rotation += angleChange; // 1.0/6.0;
    while (e.rotation > 180) e.rotation -= 360;
    while (e.rotation < -180) e.rotation += 360;
    sf::Vector2f oldVelocity = e.velocity;
    e.velocity -= sf::Vector2f(oldVelocity.x * (1.0 - e.frictionCoefficient), oldVelocity.y * (1.0 - e.frictionCoefficient));
    e.velocity += Math::fRotateAroundOrigin(
        oldVelocity.x * (1.0 - e.frictionCoefficient), 
        oldVelocity.y * (1.0 - e.frictionCoefficient),
        Math::DEG_TO_RAD*angleChange);

    std::vector<Effect> newEffects;
    for (int i = 0; i < (int)e.effects.size(); i++) {
        Effect &ef = e.effects.at(0);
        if (ef.ticks-- > 0) {
            newEffects.push_back(ef);
        }
        e.velocity += ef.force;
    }
    e.effects = newEffects;

    Collider::CollisionType collision = checkCarCollisions(e, world);
    if (collision != Collider::NONE) {
        e.x = prevX;
        e.y = prevY;
        e.rotation = prevRotation;
        if (collision == Collider::CAR_ENTITY) {
            e.velocity = {e.velocity.x/2, e.velocity.y/2};
            //e.velocity = {0, 0};
        }
        else {
            if (abs(e.velocity.x) + abs(e.velocity.y) > 1) {
                float volume = (abs(e.velocity.x) + abs(e.velocity.y))/4.0;
                volume = volume*volume;
                e.soundManager.playSound(soundManager.car_crash, volume, e.x, e.y);
            }
            e.velocity = {e.velocity.x/2, e.velocity.y/2};
            //e.velocity = {0, 0};
        }
    }
}

AtomicDrive::AtomicDrive() : world() {
    fps = 60;
    frame = 0;

    window.create(sf::VideoMode(1200, 720), "Atomic Drive");
    worldBuffer.create((int)window.getSize().x/TextureRect::SCALE_FACTOR, (int)window.getSize().y/TextureRect::SCALE_FACTOR);
    window.setFramerateLimit(fps);

    soundManager.initialize();
    TextureRect::initializeTypes();
    Tile::initializeTypes();
    world = World(128, 1);
    world.renderChunks();
    
    Entity carEntity;
    carEntity.x = 0;
    carEntity.y = 0;
    carEntity.frictionCoefficient = 0.007;
    carEntity.rotation = 30;
    carEntity.acceleration = 0.032;
    carEntity.controller = ENTITY_CONTROLLER::PLAYER_CAR;
    carEntity.sprite = &TextureRect::types[TextureRect::BLUE_CAR_BASE];
    carEntity.renderer = CAR;
    carEntity.ivars = new int[5];
    carEntity.ivars[0] = 0;
    carEntity.ivars[1] = 0;
    carEntity.ivars[2] = 0;
    carEntity.ivars[Player::ENGINE_SOUND_TICKS] = 0;
    carEntity.ivars[Player::IS_BEING_DRIVEN] = 0;

    carEntity.colliders.push_back(Collider(-8, 4, 16, 16));
    carEntity.colliders.push_back(Collider(-8, -8, 16, 16));
    carEntity.colliders.push_back(Collider(-8, -20, 16, 16));

    world.entities.push_back(carEntity);

    Entity::incrementId++;
    carEntity.id++;

    carEntity.controller = ENTITY_CONTROLLER::AI_CAR;
    delete carEntity.ivars;
    carEntity.ivars = new int[6];
    carEntity.ivars[0] = 0;
    carEntity.ivars[1] = 0;
    carEntity.ivars[2] = 0;
    carEntity.ivars[3] = 0;
    carEntity.ivars[4] = 0;
    carEntity.ivars[5] = 0;
    world.entities.push_back(carEntity);

    player = NULL;
}

void AtomicDrive::update() {
    renderResolution = {(int)worldBuffer.getSize().x, (int)worldBuffer.getSize().y};
    //player = &world.entities[1];
    if (player) {
        camera.x = (int)player->x - renderResolution.x/2;
        camera.y = (int)player->y - renderResolution.y/2;
        //std::cout << camera.x << " " << camera.y << "\n";
    }
    else {
        camera = sf::Vector2i(0.0, 0.0);
    }
    int cameraCenterX = camera.x + (int)worldBuffer.getSize().x/2;
    int cameraCenterY = camera.y + (int)worldBuffer.getSize().y/2;
    world.update();

    for (Entity &e : world.entities) {
        switch (e.controller) {
            case (ENTITY_CONTROLLER::PLAYER): {
                if (!player) {
                    player = &e;
                    e.velocity = sf::Vector2f(0.0, 0.0);
                    e.x = 16;
                    e.y = 16;
                }

                sf::Vector2f acceleration = sf::Vector2f(0.0, 0.0);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    acceleration += sf::Vector2f(0.1, 0.0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    acceleration += sf::Vector2f(-0.1, 0.0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    acceleration += sf::Vector2f(0.0, 0.1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
                ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    acceleration += sf::Vector2f(0.0, -0.1);
                }

                e.velocity += acceleration;

                if (e.velocity.x >  4) e.velocity.x =  4;
                if (e.velocity.y >  4) e.velocity.y =  4;
                if (e.velocity.x < -4) e.velocity.x = -4;
                if (e.velocity.y < -4) e.velocity.y = -4;
                e.x += e.velocity.x;
                e.y += e.velocity.y;

                break;
            }
            case (ENTITY_CONTROLLER::PLAYER_CAR): {
                if (!player) {
                    player = &e;
                    e.velocity = sf::Vector2f(0.0, 0.0);
                    e.x = 64;
                    e.y = 64;
                }
                if (e.ivars[Player::IS_BEING_DRIVEN]) {

                    float turning = 0;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                    ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        turning -= 25;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                    ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        //e.acceleration += sf::Vector2f(-0.1, 0.0);
                        turning += 25;
                    }


                    sf::Vector2f acceleration = {0.0, 0.0};

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                    ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        acceleration += Math::fRotateAroundOrigin(0, e.acceleration, (e.rotation + turning - 180)*Math::DEG_TO_RAD);
                    }

                    bool goingBack = false;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
                    ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        goingBack = true;
                        turning = -turning;
                        acceleration += Math::fRotateAroundOrigin(0, e.acceleration, (e.rotation + turning)*Math::DEG_TO_RAD);
                    }

                    //std::cout << e.ivars[Player::ENGINE_SOUND_TICKS] << std::endl;
                    
                    if (e.ivars[Player::ENGINE_SOUND_TICKS] <= 0) {
                        e.ivars[Player::ENGINE_SOUND_TICKS] = 60;
                        //std::cout << (abs(acceleration.x) + abs(acceleration.y))*10 << "\n";
                        e.soundManager.playSound(soundManager.engine_1, (abs(acceleration.x) + abs(acceleration.y))*10, e.x, e.y);
                    }
                    e.ivars[Player::ENGINE_SOUND_TICKS]--;
                    
                    calculateCarPhysics(e, turning, acceleration, goingBack, world);
                }

                break;
            }
            case (ENTITY_CONTROLLER::AI_CAR): {
                //std::cout << e.x << " " << e.y << "\n";
                float turning = 0;
                sf::Vector2f acceleration = {0.0, 0.0};

                if (e.ivars[Enemy::IS_TARGETING]) {
                    //std::cout << e.ivars[TURNING_INTO_ANGLE] << " " << e.rotation << "\n";
                    /*
                    if (!(e.ivars[TURNING_INTO_ANGLE] > e.rotation - 7 
                       && e.ivars[TURNING_INTO_ANGLE] < e.rotation + 7)) {
                        e.ivars[TURNING_DIRECTION] = 1;
                        turning = 25;
                        if (e.ivars[TURNING_INTO_ANGLE] > e.rotation + 7) std::cout << "TURNING WRONG!\n";
                        else std::cout << "TURNING RIGHT\n";
                        acceleration += Math::fRotateAroundOrigin(0, -e.acceleration, (e.rotation + turning)*Math::DEG_TO_RAD);
                    }
                    */
                    
                    if (e.ivars[Enemy::TURNING_INTO_ANGLE] > e.rotation + 7) {
                        e.ivars[Enemy::TURNING_DIRECTION] = 1;
                        turning = 25;
                    }
                    else if (e.ivars[Enemy::TURNING_INTO_ANGLE] < e.rotation - 7) {
                        e.ivars[Enemy::TURNING_DIRECTION] = 1;
                        turning = -25;
                    }
                    
                    else {
                        e.ivars[Enemy::TURNING_DIRECTION] = 0;
                    }

                    acceleration += Math::fRotateAroundOrigin(0, -e.acceleration, (e.rotation + turning)*Math::DEG_TO_RAD);
                }

                if (frame % 8 == 0 && e.ivars[Enemy::TURNING_DIRECTION] == 0) {
                    e.ivars[Enemy::TARGET_X] = player->x;
                    e.ivars[Enemy::TARGET_Y] = player->y;

                    e.ivars[Enemy::IS_TARGETING] = 1;
                    e.ivars[Enemy::TURNING_INTO_ANGLE] = -(atan2(e.x - player->x, e.y - player->y) * 180 / Math::PI);
                    //std::cout << e.x - player->x << " " << e.y - player->y << " " << e.x << " " << e.y << "\n";
                    //while (e.ivars[TURNING_INTO_ANGLE] >= 360) e.ivars[TURNING_INTO_ANGLE] -= 360;
                    //while (e.ivars[TURNING_INTO_ANGLE] < 0) e.ivars[TURNING_INTO_ANGLE] += 360;

                    //e.rotation = e.ivars[TURNING_INTO_ANGLE];
                }

                
                if (e.ivars[Enemy::ENGINE_SOUND_TICKS] <= 0) {
                    e.ivars[Enemy::ENGINE_SOUND_TICKS] = 30;
                    e.soundManager.playSound(soundManager.engine_1, (abs(acceleration.x) + abs(acceleration.y))*3, e.x, e.y);
                }
                e.ivars[Enemy::ENGINE_SOUND_TICKS]--;
                
                calculateCarPhysics(e, turning, acceleration, false, world);
                break;
            }
            default:
                break;
        }
        e.soundManager.playSounds(cameraCenterX, cameraCenterY);
    }

    //if (frame % 4 == 0) std::cout << frame << "\n";
    if (++frame >= fps) frame = 0;
}

void AtomicDrive::draw() {
    window.clear({0, 0, 0});
    worldBuffer.clear({0, 0, 0});
    world.draw(&worldBuffer, camera);
    worldBuffer.display();
    sf::Sprite s(worldBuffer.getTexture());
    s.setScale(TextureRect::SCALE_FACTOR, TextureRect::SCALE_FACTOR);
    window.draw(s);
    window.display();
    soundManager.playSounds(camera.x + (int)worldBuffer.getSize().x/2, camera.y + (int)worldBuffer.getSize().y/2);
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