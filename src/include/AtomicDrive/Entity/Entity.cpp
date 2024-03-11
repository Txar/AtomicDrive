#include "Entity.hpp"

int Entity::incrementId = 0;

Entity::Entity() {
    id = incrementId++;
}