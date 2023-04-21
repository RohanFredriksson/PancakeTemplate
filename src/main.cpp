#include "pancake/pancake.hpp"
#include "title.hpp"

using glm::vec2;
using glm::vec4;

using namespace Pancake;

void TitleInit(Scene* scene) {

    Spritesheet::load("assets/textures/king.png");

    Entity* entity;
    SpriteRenderer* spriterenderer;
    Animation* animation;
    AnimationState* state;
    FadeTransition* transition;

    // Background
    entity = new Entity(vec2(0.0f, 0.0f), vec2(5.0f, 5.0f), 0.0f);
    spriterenderer = new SpriteRenderer();
    spriterenderer->setZIndex(-1);
    spriterenderer->setColour(vec4(0.5f, 0.0f, 0.5f, 1.0f));
    entity->addComponent(spriterenderer);
    scene->addEntity(entity);

    // Transition
    entity = new Entity(vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), 0.0f);
    transition = new FadeTransition();
    transition->setDuration(1.0f);
    transition->setFrom(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    transition->setTo(vec4(0.0f, 0.0f, 0.0f, 0.0f));
    entity->addComponent(transition);
    scene->addEntity(entity);

    // Character
    entity = new Entity(vec2(0.0f, 0.0f), vec2(1.652f, 2.0f), 0.0f);
    spriterenderer = new SpriteRenderer();
    animation = new Animation();
    state = new AnimationState();
    state->setTitle("walking");
    state->setLoop(true);
    state->addFrame(SpritePool::get("king0"), 0.15f);
    state->addFrame(SpritePool::get("king1"), 0.15f);
    state->addFrame(SpritePool::get("king2"), 0.15f);
    state->addFrame(SpritePool::get("king3"), 0.15f);
    animation->addState(state);
    animation->setDefaultState("walking");
    entity->addComponent(spriterenderer);
    entity->addComponent(animation);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    return run("Title", "saves/save.scene");
    //return Pancake::run("Title", TitleInit);
}