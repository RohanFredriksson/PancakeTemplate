#pragma once

#include "pancake/pancake.hpp"
using namespace Pancake;

class PlayerController : public Component {
   
    private: 
        string state = "idle";

    public:

        PlayerController() : Component("PlayerController") {

        }

        void update(float dt) override {
            
            Animation* animation = dynamic_cast<Animation*>(this->getEntity()->getComponent("Animation"));
            Rigidbody* rigidbody = dynamic_cast<Rigidbody*>(this->getEntity()->getComponent("Rigidbody"));

            if (KeyListener::isKeyDown(GLFW_KEY_A) || KeyListener::isKeyDown(GLFW_KEY_LEFT)) {
                
                if (animation != nullptr) {

                    vec2 scale = animation->getSizeScale();
                    animation->setSizeScale(-std::abs(scale.x), scale.y);

                    if (state == "idle") {
                        animation->setState("walking");
                        this->state = "walking";
                    }

                }

                if (rigidbody != nullptr) {
                    vec2 velocity = rigidbody->getVelocity();
                    velocity.x = std::max(velocity.x - 1.0f, -4.0f);
                    rigidbody->setVelocity(velocity);
                }

            } 

            else if (KeyListener::isKeyDown(GLFW_KEY_D) || KeyListener::isKeyDown(GLFW_KEY_RIGHT)) {

                if (animation != nullptr) {

                    vec2 scale = animation->getSizeScale();
                    animation->setSizeScale(std::abs(scale.x), scale.y);

                    if (state == "idle") {
                        animation->setState("walking");
                        this->state = "walking";
                    }

                }

                if (rigidbody != nullptr) {
                    vec2 velocity = rigidbody->getVelocity();
                    velocity.x = std::min(velocity.x + 1.0f, 4.0f);
                    rigidbody->setVelocity(velocity);
                }

            } else {

                if (rigidbody != nullptr) {
                    
                    vec2 velocity = rigidbody->getVelocity();
                    bool negative = velocity.x < 0.0f;
                    velocity.x = std::max(std::abs(velocity.x) - 1.0f, 0.0f);
                    if (negative) {velocity.x *= -1.0f;}
                    rigidbody->setVelocity(velocity);

                    if (velocity.x == 0.0f && this->state == "walking") {
                        animation->setState("idle");
                        this->state = "idle";
                    }
                }

            }

        }
        
};

REGISTER(Component, PlayerController);