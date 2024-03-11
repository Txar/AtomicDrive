#pragma once

class Collider {
    public:
        int x, y;
        int width, height;
        float rotation;
        bool exists;

        enum CollisionType {
            NONE,
            GENERIC_ENTITY,
            FRAGILE_ENTITY,
            CAR_ENTITY,
            SOLID
        };

        Collider();
        Collider(int x, int y, int width, int height);

        bool collide(Collider &c);
        bool collide(Collider *c);
};