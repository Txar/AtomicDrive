#include "Collider.hpp"

Collider::Collider() {
    this->exists = false;
}

Collider::Collider(int x, int y, int width, int height) {
    this->exists = true;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->rotation = 0;
}

bool Collider::collide(Collider *c) {
    return (exists && c->exists) &&
          !(c->x > x + width || c->y > y + height
        ||  c->x + c->width < x
        ||  c->y + c->height < y);
}

bool Collider::collide(Collider &c) {
    return collide(&c);
}