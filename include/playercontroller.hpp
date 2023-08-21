#pragma once

#include "pancake/pancake.hpp"
using namespace Pancake;

class PlayerController : public Component, public CollisionListener {
   
    private: 
        string state = "idle";
        bool ground = false;

    public:

        PlayerController() : Component("PlayerController") {

        }

        void collision(Entity* with, CollisionManifold manifold) {
            if (manifold.normal.y < 0.0f) {this->ground = true;}
        }

        void update(float dt) override {

            bool left = KeyListener::isKeyDown(GLFW_KEY_A) || KeyListener::isKeyDown(GLFW_KEY_LEFT);
            bool right = KeyListener::isKeyDown(GLFW_KEY_D) || KeyListener::isKeyDown(GLFW_KEY_RIGHT);
            bool up = KeyListener::isKeyDown(GLFW_KEY_W) || KeyListener::isKeyDown(GLFW_KEY_SPACE);

            Animation* animation = dynamic_cast<Animation*>(this->getEntity()->getComponent("Animation"));
            Rigidbody* rigidbody = dynamic_cast<Rigidbody*>(this->getEntity()->getComponent("Rigidbody"));
            if (rigidbody == nullptr) {this->ground = false; return;}
            vec2 velocity = rigidbody->getVelocity();

            if (left && !right) {
                
                if (animation != nullptr) {
                    vec2 scale = animation->getSizeScale();
                    animation->setSizeScale(-std::abs(scale.x), scale.y);
                }

                velocity.x = std::max(velocity.x - 1.0f, -4.0f);
                rigidbody->setVelocity(velocity);

            } else if (right && !left) {

                if (animation != nullptr) {
                    vec2 scale = animation->getSizeScale();
                    animation->setSizeScale(std::abs(scale.x), scale.y);
                }

                velocity.x = std::min(velocity.x + 1.0f, 4.0f);
                rigidbody->setVelocity(velocity);

            } else {

                bool negative = velocity.x < 0.0f;
                velocity.x = std::max(std::abs(velocity.x) - 1.0f, 0.0f);
                if (negative) {velocity.x *= -1.0f;}
                rigidbody->setVelocity(velocity);

            }

            if (up && this->ground) {
                velocity.y = 6.0f;
                rigidbody->setVelocity(velocity);
            }

            if (animation != nullptr) {

                if (this->ground) {

                    if (velocity.x != 0.0f && this->state != "walking") {
                        animation->setState("walking"); 
                        this->state = "walking";
                    }

                    else if (velocity.x == 0.0f && this->state != "idle") {
                        animation->setState("idle"); 
                        this->state = "idle";
                    }

                } else {

                    if (velocity.y > 0.0f && this->state != "jumping") {
                        animation->setState("jumping");
                        this->state = "jumping";
                    }

                    else if (velocity.y <= 0.0f && this->state != "falling") {
                        animation->setState("falling");
                        this->state = "falling";
                    }

                }
                
            }
            
            this->ground = false;

        }
        
};

REGISTER(Component, PlayerController);