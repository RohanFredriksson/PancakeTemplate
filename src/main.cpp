#include "pancake/pancake.hpp"
#include "snake.hpp"

#include "playercontroller.hpp"
#include "mousepanhandler.hpp"

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

void PhysicsInit(Pancake::Scene* scene) {

    scene->setName("Physics");
    Pancake::Spritesheet::load("assets/textures/king.png");
    Pancake::Spritesheet::load("assets/textures/faces.png");
    Pancake::Spritesheet::load("assets/textures/world.png");

    Pancake::Entity* entity;
    Pancake::SpriteRenderer* spriterenderer;
    Pancake::TextRenderer* textrenderer;
    Pancake::Animation* animation;
    Pancake::AnimationState* state;
    Pancake::FadeTransition* transition;
    MousePanHandler* mousepanhandler;
    PlayerController* playercontroller;

    Pancake::Rigidbody* rigidbody;
    Pancake::Circle* circle;
    Pancake::Box* box;

    // Ground Sprites
    for (int i = -100; i <= 100; i++) {
        entity = new Pancake::Entity(i, -4.0f);
        spriterenderer = new Pancake::SpriteRenderer();
        spriterenderer->setSprite("dirt1");
        entity->addComponent(spriterenderer);
        scene->addEntity(entity);
    }
    
    // Ground Body
    entity = new Pancake::Entity(vec2(0.0f, -4.0f), vec2(1.0f, 1.0f), 0.0f);
    rigidbody = new Pancake::Rigidbody();
    box = new Pancake::Box();
    box->setSize(vec2(21.0f, 1.0f));
    rigidbody->addCollider(box);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

    // Background
    entity = new Pancake::Entity(0.0f, 0.0f, 100.0f, 100.0f);
    spriterenderer = new Pancake::SpriteRenderer();
    spriterenderer->setZIndex(-1);
    spriterenderer->setColour(vec4(0.4f, 0.6f, 0.7f, 1.0f));
    entity->addComponent(spriterenderer);
    scene->addEntity(entity);

    // Transition
    entity = new Pancake::Entity();
    transition = new Pancake::FadeTransition();
    transition->setDuration(0.5f);
    transition->setFrom(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    transition->setTo(vec4(0.0f, 0.0f, 0.0f, 0.0f));
    entity->addComponent(transition);
    scene->addEntity(entity);

    // Character
    entity = new Pancake::Entity(vec2(0.0f, 0.0f), vec2(1.083f, 1.5f), 0.0f);
    
    animation = new Pancake::Animation();
    state = new Pancake::AnimationState();
    state->setTitle("idle");
    state->setLoop(true);
    state->addFrame("king0", 0.15f);
    animation->addState(state);
    
    state = new Pancake::AnimationState();
    state->setTitle("walking");
    state->setLoop(true);
    state->addFrame("king0", 0.15f);
    state->addFrame("king1", 0.15f);
    state->addFrame("king2", 0.15f);
    state->addFrame("king3", 0.15f);
    animation->addState(state);

    state = new Pancake::AnimationState();
    state->setTitle("jumping");
    state->setLoop(false);
    state->addFrame("king4", 0.15f);
    state->addFrame("king5", 0.15f);
    animation->addState(state);

    state = new Pancake::AnimationState();
    state->setTitle("falling");
    state->setLoop(true);
    state->addFrame("king6", 0.15f);
    animation->addState(state);

    state = new Pancake::AnimationState();
    state->setTitle("landing");
    state->setLoop(true);
    state->addFrame("king7", 0.15f);
    animation->addState(state);

    animation->setDefaultState("idle");
    entity->addComponent(animation);
    
    rigidbody = new Pancake::Rigidbody();
    rigidbody->setFriction(0.0f);
    rigidbody->setRestitution(0.01f);
    rigidbody->setFixedOrientation(true);
    
    box = new Pancake::Box();
    box->setSize(0.75f, 0.75f);
    box->setMass(1.0f);
    rigidbody->addCollider(box);

    circle = new Pancake::Circle();
    circle->setRadius(0.375f);
    circle->setMass(1.0f);
    circle->setPositionOffset(0.0f, -0.375f);
    rigidbody->addCollider(circle);
    
    circle = new Pancake::Circle();
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
            
            entity = new Pancake::Entity(cursor.x, cursor.y);

            rigidbody = new Pancake::Rigidbody();
            box = new Pancake::Box();
            box->setMass(3.0f);
            box->setSize(vec2(0.75f, 0.75f));
            rigidbody->addCollider(box);
            rigidbody->setFriction(0.75f);
            rigidbody->setRestitution(0.3f);
            entity->addComponent(rigidbody);

            spriterenderer = new Pancake::SpriteRenderer();
            spriterenderer->setSprite("crate0");
            entity->addComponent(spriterenderer);

            scene->addEntity(entity);

            cursor.x += width + gap;

        }

        cursor.x = start + 0.5f * (width + gap);
        cursor.y += height + gap;

    }

    // Text
    entity = new Pancake::Entity(vec2(0.0f, 3.0f), vec2(1.0f, 1.0f), 0.0f);
    textrenderer = new Pancake::TextRenderer();
    textrenderer->setText("Hello World!");
    textrenderer->setColour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    entity->addComponent(textrenderer);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    Pancake::title("Template");
    Pancake::icon("assets/icons/house.png");
    //Pancake::load(SnakeInit);
    Pancake::load(PhysicsInit);
    Pancake::projection(12);
    Pancake::height(800);
    Pancake::width(1200);
    Pancake::start();
}