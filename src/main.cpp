#include "pancake/pancake.hpp"
#include "title.hpp"

using glm::vec2;
using glm::vec4;

using namespace Pancake;

void TitleInit(Scene* scene) {

    Spritesheet::load("assets/textures/king.png");

    Entity* entity;
    SpriteRenderer* spriterenderer;
    TextRenderer* textrenderer;
    Animation* animation;
    AnimationState* state;
    FadeTransition* transition;

    Rigidbody* rigidbody;
    Circle* circle;
    Box* box;
    
    // Ground
    entity = new Entity(vec2(0.0f, -5.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setSize(vec2(10.0f, 1.0f));
    rigidbody->addCollider(box);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);
    
    // Single Box
    entity = new Entity(vec2(-2.0f, 0.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setMass(1.0f);
    box->setSize(vec2(2.0f, 1.0f));
    box->setRotationOffset(1.0f);
    rigidbody->addCollider(box);
    rigidbody->setFriction(0.2f);
    rigidbody->setRestitution(0.5f);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

    // Double box
    entity = new Entity(vec2(2.0f, 0.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setMass(0.5f);
    box->setPositionOffset(vec2(0.5f, 0.0f));
    box->setSize(vec2(1.0f, 1.0f));
    rigidbody->addCollider(box);
    box = new Box();
    box->setMass(0.5f);
    box->setPositionOffset(vec2(-0.5f, 0.0f));
    rigidbody->addCollider(box);
    rigidbody->setFriction(0.2f);
    rigidbody->setRestitution(0.5f);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);
    
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
    entity->addComponent(animation);
    scene->addEntity(entity);

    // Text
    entity = new Entity(vec2(0.0f, 3.0f), vec2(1.0f, 1.0f), 0.0f);
    textrenderer = new TextRenderer();
    textrenderer->setText("Hello World!");
    textrenderer->setColour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    entity->addComponent(textrenderer);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    return run("Title", "saves/test.scene");
    //return Pancake::run("Title", TitleInit);
}