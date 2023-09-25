#include "snake.hpp"

Snake::Snake() : Component("Snake") {

    this->alive = true;
    this->progress = 0.0f;
    this->speed = 10.0f;
    this->direction = SnakeDirection::RIGHT;

    for (int i = 0; i < 5; i++) {this->body.push_back(glm::ivec2(-2 + i, 0));}

}

void Snake::start() {

    for (int i = 0; i < this->body.size(); i++) {
        Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(this->body[i].x, this->body[i].y);
        sprite->setColour(1.0f, 1.0f, 1.0f, 1.0f);
        this->getEntity()->addComponent(sprite);
        this->sprites.push_back(sprite);
    }

}

void Snake::update(float dt) {

    // If the snake is dead, don't update it.
    if (!this->alive) {return;}

    // Check for key presses.
    glm::ivec2 next;
    bool pressed = false;
    
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_UP)) {next = SnakeDirection::UP; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_DOWN)) {next = SnakeDirection::DOWN; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_RIGHT)) {next = SnakeDirection::RIGHT; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_LEFT)) {next = SnakeDirection::LEFT; pressed = true;}

    if (pressed && this->inputs.size() == 0 && next != this->direction && next != -1 * this->direction) {this->inputs.push_back(next);}
    else if (pressed && this->inputs.size() > 0 && this->inputs.size() < 3 && next != this->inputs[0] && next != -1 * this->inputs[0]) {this->inputs.push_back(next);}

    this->progress += this->speed * dt;

    // Check if there is a crash
    next = this->body[this->body.size()-1] + this->direction;
    for (int i = 0; i < this->body.size(); i++) {
        if (this->body[i] == next) {this->alive = false;}
    }

    // Move the snake if it has reached the next unit.
    if (this->progress < 1.0f) {return;}

    this->body.push_back(this->body[this->body.size()-1] + this->direction);
    this->body.erase(this->body.begin());

    for (int i = 0; i < this->sprites.size(); i++) {
        this->sprites[i]->setPositionOffset(this->body[i].x, this->body[i].y);
    }

    if (this->inputs.size() > 0) {
        this->direction = this->inputs[0]; 
        this->inputs.erase(this->inputs.begin());
    }

    this->progress -= 1.0f;

}