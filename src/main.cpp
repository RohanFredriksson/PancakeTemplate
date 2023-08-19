#include "pancake/pancake.hpp"
#include "mousepanhandler.hpp"
#include "playercontroller.hpp"

using glm::vec2;
using glm::vec4;

using namespace Pancake;

void TitleInit(Scene* scene) {

    scene->setName("Title");
    Spritesheet::load("assets/textures/king.png");
    Spritesheet::load("assets/textures/faces.png");
    Spritesheet::load("assets/textures/world.png");

    Entity* entity;
    SpriteRenderer* spriterenderer;
    TextRenderer* textrenderer;
    Animation* animation;
    AnimationState* state;
    FadeTransition* transition;
    MousePanHandler* mousepanhandler;
    PlayerController* playercontroller;

    Rigidbody* rigidbody;
    Circle* circle;
    Box* box;

    // Ground
    for (int i = -100; i <= 100; i++) {
        entity = new Entity(i, -4.0f);
        spriterenderer = new SpriteRenderer();
        spriterenderer->setSprite("dirt1");
        entity->addComponent(spriterenderer);
        scene->addEntity(entity);
    }

    // Mouse Movement Handler
    //entity = new Entity();
    //mousepanhandler = new MousePanHandler();
    //entity->addComponent(mousepanhandler);
    //scene->addEntity(entity);

    // Ground
    entity = new Entity(vec2(0.0f, -4.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setSize(vec2(21.0f, 1.0f));
    rigidbody->addCollider(box);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

    // Single Box
    entity = new Entity(vec2(-1.0f, 2.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setMass(1.0f);
    box->setSize(vec2(0.5f, 1.0f));
    box->setRotationOffset(0.5f);
    rigidbody->addCollider(box);
    rigidbody->setFriction(0.15f);
    rigidbody->setRestitution(0.3f);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

    // Circle
    entity = new Entity(vec2(1.5f, 2.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    circle = new Circle();
    circle->setMass(1.0f);
    circle->setRadius(0.5f);
    rigidbody->addCollider(circle);
    rigidbody->setFriction(0.2f);
    rigidbody->setRestitution(0.3f);
    entity->addComponent(rigidbody);
    spriterenderer = new SpriteRenderer();
    spriterenderer->setSprite(SpritePool::get("chest0"));
    entity->addComponent(spriterenderer);
    scene->addEntity(entity);

    // Background
    entity = new Entity(0.0f, 0.0f, 100.0f, 100.0f);
    spriterenderer = new SpriteRenderer();
    spriterenderer->setZIndex(-1);
    spriterenderer->setColour(vec4(0.4f, 0.6f, 0.7f, 1.0f));
    entity->addComponent(spriterenderer);
    scene->addEntity(entity);

    // Transition
    entity = new Entity(vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), 0.0f);
    transition = new FadeTransition();
    transition->setDuration(1.0f);
    transition->setFrom(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    transition->setTo(vec4(0.0f, 0.0f, 0.0f, 0.0f));
    entity->addComponent(transition);
    //scene->addEntity(entity);

    // Character
    entity = new Entity(vec2(0.0f, 0.0f), vec2(1.083f, 1.5f), 0.0f);
    
    animation = new Animation();
    state = new AnimationState();
    state->setTitle("idle");
    state->setLoop(true);
    state->addFrame("king0", 0.15f);
    animation->addState(state);
    
    state = new AnimationState();
    state->setTitle("walking");
    state->setLoop(true);
    state->addFrame("king0", 0.15f);
    state->addFrame("king1", 0.15f);
    state->addFrame("king2", 0.15f);
    state->addFrame("king3", 0.15f);
    animation->addState(state);

    state = new AnimationState();
    state->setTitle("jumping");
    state->setLoop(false);
    state->addFrame("king4", 0.15f);
    state->addFrame("king5", 0.15f);
    animation->addState(state);

    state = new AnimationState();
    state->setTitle("falling");
    state->setLoop(true);
    state->addFrame("king6", 0.15f);
    animation->addState(state);

    state = new AnimationState();
    state->setTitle("landing");
    state->setLoop(true);
    state->addFrame("king7", 0.15f);
    animation->addState(state);

    animation->addTransfer("idle", "walking", "left");
    animation->addTransfer("idle", "walking", "right");
    animation->addTransfer("idle", "jumping", "up");
    animation->addTransfer("idle", "falling", "down");

    animation->addTransfer("jumping", "falling", "down");
    animation->addTransfer("jumping", "walking", "ground");
    animation->addTransfer("walking", "jumping", "up");
    animation->addTransfer("landing", "jumping", "up");

    

    animation->setDefaultState("idle");
    entity->addComponent(animation);
    
    rigidbody = new Rigidbody();
    rigidbody->setFriction(0.0f);
    rigidbody->setRestitution(0.01f);
    rigidbody->setFixedOrientation(true);
    
    box = new Box();
    box->setSize(0.75f, 0.75f);
    box->setMass(1.0f);
    rigidbody->addCollider(box);

    circle = new Circle();
    circle->setRadius(0.375f);
    circle->setMass(1.0f);
    circle->setPositionOffset(0.0f, -0.375f);
    rigidbody->addCollider(circle);
    
    circle = new Circle();
    circle->setRadius(0.375f);
    circle->setMass(1.0f);
    circle->setPositionOffset(0.0f, 0.375f);
    rigidbody->addCollider(circle);

    entity->addComponent(rigidbody);

    playercontroller = new PlayerController();
    entity->addComponent(playercontroller);

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
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    Pancake::load(TitleInit);
    Pancake::projection(9);
    //Pancake::width(1920);
    Pancake::start();
}