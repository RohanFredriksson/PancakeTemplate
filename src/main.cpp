#include "pancake/pancake.hpp"
#include "snake_map.hpp"
#include "snake.hpp"

void SnakeInit(Pancake::Scene* scene) {

    scene->setName("Snake Game");
    Pancake::Spritesheet::load("assets/textures/snake.png");
    Pancake::Spritesheet::load("assets/textures/snake_floor.png");
    Pancake::Spritesheet::load("assets/textures/snake_border.png");

    Pancake::Entity* entity = new Pancake::Entity();

    Snake* snake = new Snake();
    entity->addComponent(snake);

    SnakeMap* map = new SnakeMap();
    //map->setBounds(glm::ivec2(-10, -2), glm::ivec2(10, 5));
    entity->addComponent(map);

    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    Pancake::load(SnakeInit);
    Pancake::projection(12);
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}