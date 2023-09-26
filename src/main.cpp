#include "pancake/pancake.hpp"
#include "snake.hpp"

void SnakeInit(Pancake::Scene* scene) {

    scene->setName("Snake Game");
    Pancake::Spritesheet::load("assets/textures/snake.png");

    Pancake::Entity* entity = new Pancake::Entity();
    Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
    sprite->setSizeScale(100, 100);
    sprite->setColour(0.5f, 0.5f ,0.5f, 1.0f);
    sprite->setZIndex(-1);
    entity->addComponent(sprite);
    scene->addEntity(entity);

    entity = new Pancake::Entity();
    Snake* snake = new Snake();
    entity->addComponent(snake);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    Pancake::load(SnakeInit);
    Pancake::projection(11);
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}