#include <cmath>
#include "snake.hpp"

namespace {
    const glm::ivec2 UP    = glm::ivec2( 0,  1);
    const glm::ivec2 DOWN  = glm::ivec2( 0, -1);
    const glm::ivec2 LEFT  = glm::ivec2(-1,  0);
    const glm::ivec2 RIGHT = glm::ivec2( 1,  0);
}

Snake::Snake() : Component("Snake") {

    this->alive = true;
    this->progress = 0.0f;
    this->speed = 5.0f;
    this->direction = RIGHT;

    for (int i = 0; i < 5; i++) {this->bodies.push_back(glm::ivec2(-2 + i, 0));}

}

void Snake::head() {

    // Head
    this->endSprites[0]->setPositionOffset(this->bodies[this->bodies.size()-1].x + this->progress * this->direction.x, this->bodies[this->bodies.size()-1].y + this->progress * this->direction.y);
    if      (this->direction == LEFT)  {this->endSprites[0]->setRotationOffset(0.0f * M_PI);}
    else if (this->direction == DOWN)  {this->endSprites[0]->setRotationOffset(0.5f * M_PI);}
    else if (this->direction == RIGHT) {this->endSprites[0]->setRotationOffset(1.0f * M_PI);}
    else if (this->direction == UP)    {this->endSprites[0]->setRotationOffset(1.5f * M_PI);}

    // Head to body
    this->endSprites[2]->setPositionOffset(this->bodies[this->bodies.size()-1].x + 0.5f * this->progress * this->direction.x, this->bodies[this->bodies.size()-1].y + 0.5f * this->progress * this->direction.y);
    if      (this->direction == LEFT || this->direction == RIGHT) {this->endSprites[2]->setSizeScale(this->progress, 1.0f); this->endSprites[2]->setSprite("snake_horizontal");}
    else if (this->direction == DOWN || this->direction == UP)    {this->endSprites[2]->setSizeScale(1.0f, this->progress); this->endSprites[2]->setSprite("snake_vertical");}

}

void Snake::tail() {

    // Tail
    this->endSprites[1]->setPositionOffset(this->bodies[0].x + this->progress * (this->bodies[1] - this->bodies[0]).x, this->bodies[0].y + this->progress * (this->bodies[1] - this->bodies[0]).y);
    if      (this->bodies[1] - this->bodies[0] == LEFT)  {this->endSprites[1]->setRotationOffset(0.0f * M_PI);}
    else if (this->bodies[1] - this->bodies[0] == DOWN)  {this->endSprites[1]->setRotationOffset(0.5f * M_PI);}
    else if (this->bodies[1] - this->bodies[0] == RIGHT) {this->endSprites[1]->setRotationOffset(1.0f * M_PI);}
    else if (this->bodies[1] - this->bodies[0] == UP)    {this->endSprites[1]->setRotationOffset(1.5f * M_PI);}

    // Tail to body
    this->endSprites[3]->setPositionOffset((this->bodies[1].x + this->bodies[0].x + this->progress * (this->bodies[1] - this->bodies[0]).x) * 0.5f, (this->bodies[1].y + this->bodies[0].y + this->progress * (this->bodies[1] - this->bodies[0]).y) * 0.5f);
    if      (((this->bodies[1] - this->bodies[0]) == LEFT) || ((this->bodies[1] - this->bodies[0]) == RIGHT)) {this->endSprites[3]->setSizeScale(1.0f - this->progress, 1.0f); this->endSprites[3]->setSprite("snake_horizontal");}
    else if (((this->bodies[1] - this->bodies[0]) == DOWN) || ((this->bodies[1] - this->bodies[0]) == UP))    {this->endSprites[3]->setSizeScale(1.0f, 1.0f - this->progress); this->endSprites[3]->setSprite("snake_vertical");}

}

void Snake::body(bool changed) {

    for (int i = 0; i < this->bodySprites.size(); i++) {this->bodySprites[i]->kill();}
    this->bodySprites.clear();

    // Determine the number of nodes in the snake.
    std::vector<glm::ivec2> nodes;
    nodes.push_back(this->bodies[this->bodies.size()-1]);
    for (int i = this->bodies.size()-2; i > 1; i--) {if (this->bodies[i+1] - this->bodies[i] != this->bodies[i] - this->bodies[i-1]) {nodes.push_back(this->bodies[i]);}}
    nodes.push_back(this->bodies[1]);

    // Put the bend sprites where the snake bends.
    Pancake::SpriteRenderer* sprite;
    for (int i = 1; i < nodes.size() - 1; i++) {

        // Create a new sprite renderer for the bend.
        sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(nodes[i].x, nodes[i].y);
        sprite->setSprite("snake_bend");
        sprite->setZIndex(1);

        // Determine the direction of the bend.
        glm::ivec2 p = nodes[i] - nodes[i-1];
        p.x = p.x > 0 ? 1 : (p.x < 0 ? -1 : 0);
        p.y = p.y > 0 ? 1 : (p.y < 0 ? -1 : 0);
        
        glm::ivec2 n = nodes[i+1] - nodes[i];
        n.x = n.x > 0 ? 1 : (n.x < 0 ? -1 : 0);
        n.y = n.y > 0 ? 1 : (n.y < 0 ? -1 : 0);

        // Rotate the bend sprite if necessary.
        if      ((p == LEFT && n == UP) || (p == DOWN && n == RIGHT)) {sprite->setRotationOffset(1.0f * M_PI);}
        else if ((p == RIGHT && n == UP) || (p == DOWN && n == LEFT)) {sprite->setRotationOffset(1.5f * M_PI);}
        else if ((p == UP && n == RIGHT) || (p == LEFT && n == DOWN)) {sprite->setRotationOffset(0.5f * M_PI);}

        // Add the sprite renderer.
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);

    }

    // Put sprites for each straight section of the snake.
    for (int i = 0; i < nodes.size()-1; i++) {
        
        // Create a sprite renderer for each gap between the bends.
        sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(((float) nodes[i].x + (float) nodes[i+1].x) * 0.5f, ((float) nodes[i].y + (float) nodes[i+1].y) * 0.5f);
        sprite->setSizeScale(std::max(std::abs(nodes[i].x - nodes[i+1].x), 1), std::max(std::abs(nodes[i].y - nodes[i+1].y), 1));
        
        // Determine if it is horizontal or vertical.
        if (nodes[i].x - nodes[i+1].x == 0) {sprite->setSprite("snake_vertical");}
        else {sprite->setSprite("snake_horizontal");}

        // Add the sprite renderer.
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);

    }

    if (changed) {

        // Create a new sprite renderer for the bend.
        sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(this->bodies[this->bodies.size()-1].x, this->bodies[this->bodies.size()-1].y);
        sprite->setSprite("snake_bend");
        sprite->setZIndex(1);

        // Determine the direction of the bend.
        glm::ivec2 p = this->bodies[this->bodies.size()-1] - this->bodies[this->bodies.size()-2];
        p.x = p.x > 0 ? 1 : (p.x < 0 ? -1 : 0);
        p.y = p.y > 0 ? 1 : (p.y < 0 ? -1 : 0);
        
        // Rotate the bend sprite if necessary.
        glm::ivec2 n = this->direction;
        if      ((p == LEFT && n == UP) || (p == DOWN && n == RIGHT)) {sprite->setRotationOffset(1.0f * M_PI);}
        else if ((p == RIGHT && n == UP) || (p == DOWN && n == LEFT)) {sprite->setRotationOffset(1.5f * M_PI);}
        else if ((p == UP && n == RIGHT) || (p == LEFT && n == DOWN)) {sprite->setRotationOffset(0.5f * M_PI);}

        // Add the sprite renderer.
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);

    }

    // Check if the tail requires a bend.
    if ((this->bodies[1] - this->bodies[0]) != (this->bodies[2] - this->bodies[1])) {
        
        // Create a new sprite renderer for the bend.
        sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(this->bodies[1].x, this->bodies[1].y);
        sprite->setSprite("snake_bend");
        sprite->setZIndex(1);

        // Determine the direction of the bend.
        glm::ivec2 p = this->bodies[1] - this->bodies[0];
        p.x = p.x > 0 ? 1 : (p.x < 0 ? -1 : 0);
        p.y = p.y > 0 ? 1 : (p.y < 0 ? -1 : 0);
        
        glm::ivec2 n = this->bodies[2] - this->bodies[1];
        n.x = n.x > 0 ? 1 : (n.x < 0 ? -1 : 0);
        n.y = n.y > 0 ? 1 : (n.y < 0 ? -1 : 0);

        // Rotate the bend sprite if necessary.
        if      ((p == LEFT && n == UP) || (p == DOWN && n == RIGHT)) {sprite->setRotationOffset(1.0f * M_PI);}
        else if ((p == RIGHT && n == UP) || (p == DOWN && n == LEFT)) {sprite->setRotationOffset(1.5f * M_PI);}
        else if ((p == UP && n == RIGHT) || (p == LEFT && n == DOWN)) {sprite->setRotationOffset(0.5f * M_PI);}

        // Add the sprite renderer.
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);

    }

    // After updating the body, we need to fix the tail connection.
    this->tail();

}

void Snake::start() {

    for (int i = 0; i < this->bodies.size(); i++) {
        Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
        sprite->setPositionOffset(this->bodies[i].x, this->bodies[i].y);
        this->getEntity()->addComponent(sprite);
        this->bodySprites.push_back(sprite);
    }
    
    // Head of the snake
    Pancake::SpriteRenderer* sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->bodies[this->bodies.size()-1].x, this->bodies[this->bodies.size()-1].y);
    sprite->setSprite("snake_head");
    sprite->setZIndex(2);
    this->getEntity()->addComponent(sprite);
    this->endSprites.push_back(sprite);

    // Tail of the snake.
    sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->bodies[0].x, this->bodies[0].y);
    sprite->setSprite("snake_tail");
    this->getEntity()->addComponent(sprite);
    sprite->setZIndex(0);
    this->endSprites.push_back(sprite);

    // Head to body.
    sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->bodies[this->bodies.size()-1].x, this->bodies[this->bodies.size()-1].y);
    sprite->setSprite("snake_horizontal");
    sprite->setZIndex(1);
    this->getEntity()->addComponent(sprite);
    this->endSprites.push_back(sprite);

    // Tail to body.
    sprite = new Pancake::SpriteRenderer();
    sprite->setPositionOffset(this->bodies[0].x, this->bodies[0].y);
    sprite->setSprite("snake_horizontal");
    sprite->setZIndex(1);
    this->getEntity()->addComponent(sprite);
    this->endSprites.push_back(sprite);

}

void Snake::update(float dt) {

    // If the snake is dead, don't update it.
    if (!this->alive) {return;}

    // Check for key presses.
    glm::ivec2 next;
    bool pressed = false;
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_UP)) {next = UP; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_DOWN)) {next = DOWN; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_RIGHT)) {next = RIGHT; pressed = true;}
    if (Pancake::KeyListener::isKeyBeginDown(GLFW_KEY_LEFT)) {next = LEFT; pressed = true;}

    if (pressed && this->inputs.size() == 0 && next != this->direction && next != -1 * this->direction) {this->inputs.push_back(next);}
    else if (pressed && this->inputs.size() > 0 && this->inputs.size() < 3 && next != this->inputs[0] && next != -1 * this->inputs[0]) {this->inputs.push_back(next);}

    this->progress += this->speed * dt;

    // Check if there is a crash
    next = this->bodies[this->bodies.size()-1] + this->direction;
    for (int i = 0; i < this->bodies.size(); i++) {
        if (this->bodies[i] == next) {this->alive = false;}
    }

    // Rerender the head and tail of the snake.
    this->head();
    this->tail();

    // Move the snake if it has reached the next unit.
    if (this->progress < 1.0f) {return;}
    this->bodies.push_back(this->bodies[this->bodies.size()-1] + this->direction);
    this->bodies.erase(this->bodies.begin());

    // Take the next input from the queue if there is one.
    bool changed = false;
    if (this->inputs.size() > 0) {
        this->direction = this->inputs[0]; 
        this->inputs.erase(this->inputs.begin());
        changed = true;
    }

    // Reset the progress.
    this->progress -= 1.0f;

    // Rerender the body
    this->body(changed);

}