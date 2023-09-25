#include <cmath>
#include "snake.hpp"

Snake::Snake() : Component("Snake") {

    this->alive = true;
    this->progress = 0.0f;
    this->speed = 10.0f;
    this->direction = SnakeDirection::RIGHT;

    for (int i = 0; i < 10; i++) {this->body.push_back(glm::ivec2(-2 + i, 0));}

}

void Snake::start() {

    for (int i = 0; i < this->body.size(); i++) {
        Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(this->body[i].x, this->body[i].y);
        sprite->setColour(1.0f, 1.0f, 1.0f, 1.0f);
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);
    }

    
    //sprite->setPositionOffset(this->body[0].x, this->body[0].y);
    //this->getEntity()->addComponent(sprite);

    //

    // endSprites[0] = Head of the snake
    Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->body[this->body.size()-1].x, this->body[this->body.size()-1].y);
    sprite->setColour(1.0, 1.0f, 0.0f, 1.0f);
    sprite->setSprite("snake_head");
    sprite->setZIndex(2);
    this->getEntity()->addComponent(sprite);
    this->endSprites.push_back(sprite);

    // endSprites[1] Tail of the snake.
    sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->body[0].x, this->body[0].y);
    sprite->setColour(0.0, 1.0f, 1.0f, 1.0f);
    this->getEntity()->addComponent(sprite);
    this->endSprites.push_back(sprite);

    // endSprites[2] Head to body of the snake.

    // endSprites[3] Tail to body of the snake.

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

    // Rerender the head and tail of the snake
    glm::vec2 head = glm::vec2(this->body[this->body.size()-1].x + this->progress * this->direction.x, this->body[this->body.size()-1].y + this->progress * this->direction.y);
    this->endSprites[0]->setPositionOffset(head);
    if      (this->direction == SnakeDirection::LEFT)  {this->endSprites[0]->setRotationOffset(0);}
    else if (this->direction == SnakeDirection::RIGHT) {this->endSprites[0]->setRotationOffset(M_PI);}
    else if (this->direction == SnakeDirection::UP)    {this->endSprites[0]->setRotationOffset(M_PI / -2.0);}
    else if (this->direction == SnakeDirection::DOWN)  {this->endSprites[0]->setRotationOffset(M_PI / 2.0);}

    glm::ivec2 tailDirection = this->body[1] - this->body[0];        
    glm::vec2 tail = glm::vec2(this->body[0].x + this->progress * tailDirection.x, this->body[0].y + this->progress * tailDirection.y);
    this->endSprites[1]->setPositionOffset(tail);

    // Move the snake if it has reached the next unit.
    if (this->progress < 1.0f) {return;}

    this->body.push_back(this->body[this->body.size()-1] + this->direction);
    this->body.erase(this->body.begin());

    // Rerender the body
    for (int i = 0; i < this->bodySprites.size(); i++) {this->bodySprites[i]->kill();}
    this->bodySprites.clear();

    // Determine the number of nodes in the snake.
    std::vector<glm::ivec2> nodes;
    nodes.push_back(this->body[this->body.size()-1]);
    for (int i = this->body.size()-2; i > 1; i--) {if (this->body[i+1] - this->body[i] != this->body[i] - this->body[i-1]) {nodes.push_back(this->body[i]);}}
    nodes.push_back(this->body[1]);

    for (int i = 0; i < nodes.size(); i++) {
        Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(nodes[i].x, nodes[i].y);
        sprite->setSprite("snake_bend");
        sprite->setZIndex(1);
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);
    }

    for (int i = 0; i < nodes.size()-1; i++) {
        
        Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(((float) nodes[i].x + (float) nodes[i+1].x) * 0.5f, ((float) nodes[i].y + (float) nodes[i+1].y) * 0.5f);
        sprite->setSizeScale(std::max(std::abs(nodes[i].x - nodes[i+1].x), 1), std::max(std::abs(nodes[i].y - nodes[i+1].y), 1));
        
        if (nodes[i].x - nodes[i+1].x == 0) {sprite->setSprite("snake_vertical");}
        else {sprite->setSprite("snake_horizontal");}

        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);

    }

    if (this->inputs.size() > 0) {
        this->direction = this->inputs[0]; 
        this->inputs.erase(this->inputs.begin());
    }

    this->progress -= 1.0f;

}