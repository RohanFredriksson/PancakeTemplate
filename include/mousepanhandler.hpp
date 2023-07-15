#pragma once

#include "pancake/pancake.hpp"
using namespace Pancake;

class MousePanHandler : public Component {
   
    public:

        MousePanHandler() : Component("MousePanHandler") {

        }

        void update(float dt) override {
            
            if (MouseListener::isMouseDragging()) {
                if (MouseListener::getDx() != 0) {Window::getScene()->getCamera()->addPosition(vec2(-MouseListener::getWorldDx(), 0.0f));}
                if (MouseListener::getDy() != 0) {Window::getScene()->getCamera()->addPosition(vec2(0.0f, MouseListener::getWorldDy()));}
            }

        } 
        
};

REGISTER(Component, MousePanHandler);