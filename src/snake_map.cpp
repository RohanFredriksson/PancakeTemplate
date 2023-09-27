#include <chrono>
#include <random>

#include "snake_map.hpp"

SnakeMap::SnakeMap() : Pancake::Component("SnakeMap") {
    this->bounds[0] = glm::ivec2(-5, -5);
    this->bounds[1] = glm::ivec2( 5,  5);
    this->dirty = true;
}

void SnakeMap::update(float dt) {

    if (!this->dirty) {return;}

    for (Pancake::SpriteRenderer* sprite : this->sprites) {sprite->kill();}
    this->sprites.clear();

    for (int i = bounds[0].x + 1; i < bounds[1].x; i++) {
        for (int j = bounds[0].y + 1; j < bounds[1].y; j++) {
            Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
            sprite->setZIndex(-1);
            sprite->setPositionOffset(i, j);
            if ((i + j) % 2 == 0) {sprite->setSprite("snake_floor_dark");}
            else {sprite->setSprite("snake_floor_light");}
            this->getEntity()->addComponent(sprite);
        }
    }

    this->dirty = false;

}

void SnakeMap::setBounds(glm::ivec2 min, glm::ivec2 max) {
    this->bounds[0] = min;
    this->bounds[1] = max;
    this->dirty = true;
}