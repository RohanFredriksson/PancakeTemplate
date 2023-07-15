#pragma once

#include "pancake/pancake.hpp"
using namespace Pancake;

class TitleComponent : public Component {
   
    public:

        TitleComponent() : Component("TitleComponent") {

        }

        void update(float dt) override {
            
             if (MouseListener::isMouseBeginDown(GLFW_MOUSE_BUTTON_LEFT)) {
        
                Component* c = this->getEntity()->getComponent("AudioPlayer");
                if (c == nullptr) {return;}
                
                AudioPlayer* a = dynamic_cast<AudioPlayer*>(c);
                a->play();

            }

        } 
        
};

REGISTER(Component, TitleComponent);