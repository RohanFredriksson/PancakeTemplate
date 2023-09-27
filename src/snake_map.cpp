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

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> type(0, 6);
    std::uniform_int_distribution<int> variant(0, 6);

    for (int i = bounds[0].x + 1; i < bounds[1].x; i++) {
        for (int j = bounds[0].y + 1; j < bounds[1].y; j++) {

            Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
            sprite->setZIndex(-1);
            sprite->setPositionOffset(i, j);

            std::string name = std::string("snake_floor_") + (((i + j) % 2 == 0) ? "dark" : "light");
            if (type(mt) == 0) {name += "_variant_" + std::to_string(variant(mt));}

            sprite->setSprite(name);

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

std::array<glm::ivec2, 2> SnakeMap::getBounds() {
    return this->bounds;
}