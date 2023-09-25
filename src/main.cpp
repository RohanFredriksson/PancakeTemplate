#include "pancake/pancake.hpp"
#include "snake.hpp"

void SnakeInit(Pancake::Scene* scene) {

    scene->setName("Snake Game");
    Pancake::Spritesheet::load("assets/textures/snake.png");

    Pancake::Entity* entity = new Pancake::Entity();
    Snake* snake = new Snake();
    entity->addComponent(snake);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    Pancake::load(SnakeInit);
    Pancake::projection(15);
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}