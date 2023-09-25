#include "pancake/pancake.hpp"
#include "mousepanhandler.hpp"
#include "playercontroller.hpp"
#include "snake.hpp"

using glm::vec2;
using glm::vec4;

using namespace Pancake;

void TitleInit(Scene* scene) {

    scene->setName("Title");
    Spritesheet::load("assets/textures/king.png");
    Spritesheet::load("assets/textures/faces.png");
    Spritesheet::load("assets/textures/world.png");

    Entity* entity = new Entity();
    Snake* snake = new Snake();
    entity->addComponent(snake);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    Pancake::load(TitleInit);
    Pancake::projection(81);
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}