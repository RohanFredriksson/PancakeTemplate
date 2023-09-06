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

    // Ground Sprites
    for (int i = -100; i <= 100; i++) {
        entity = new Entity(i, -4.0f);
        spriterenderer = new SpriteRenderer();
        spriterenderer->setSprite("dirt1");
        entity->addComponent(spriterenderer);
        scene->addEntity(entity);
    }
    
    // Ground Body
    entity = new Entity(vec2(0.0f, -4.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Rigidbody();
    box = new Box();
    box->setSize(vec2(21.0f, 1.0f));
    rigidbody->addCollider(box);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

    // Background
    entity = new Entity(0.0f, 0.0f, 100.0f, 100.0f);
    spriterenderer = new SpriteRenderer();
    spriterenderer->setZIndex(-1);
    spriterenderer->setColour(vec4(0.4f, 0.6f, 0.7f, 1.0f));
    entity->addComponent(spriterenderer);
    scene->addEntity(entity);

    // Transition
    entity = new Entity();
    transition = new FadeTransition();
    transition->setDuration(0.5f);
    transition->setFrom(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    transition->setTo(vec4(0.0f, 0.0f, 0.0f, 0.0f));
    entity->addComponent(transition);
    scene->addEntity(entity);

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

    // Crates
    float gap = 0.1f;
    float width = 0.75f;
    float height = 0.75f;
    vec2 cursor = vec2(2, -3.0f);

    for (int i = 3; i > 0; i--) {
        
        float start = cursor.x;
        for (int j = 0; j < i; j++) {
            
            entity = new Entity(cursor.x, cursor.y);

            rigidbody = new Rigidbody();
            box = new Box();
            box->setMass(3.0f);
            box->setSize(vec2(0.75f, 0.75f));
            rigidbody->addCollider(box);
            rigidbody->setFriction(0.75f);
            rigidbody->setRestitution(0.3f);
            entity->addComponent(rigidbody);

            spriterenderer = new SpriteRenderer();
            spriterenderer->setSprite("crate0");
            entity->addComponent(spriterenderer);

            scene->addEntity(entity);

            cursor.x += width + gap;

        }

        cursor.x = start + 0.5f * (width + gap);
        cursor.y += height + gap;

    }

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
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}