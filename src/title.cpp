#include "title.hpp"

TitleComponent::TitleComponent() : Component("TitleComponent") {

}

void TitleComponent::update(float dt) {

    if (MouseListener::isMouseBeginDown(GLFW_MOUSE_BUTTON_LEFT)) {
        
        Component* c = this->getEntity()->getComponentByType("AudioPlayer");
        if (c == nullptr) {return;}
        
        AudioPlayer* a = dynamic_cast<AudioPlayer*>(c);
        a->play();

    }

}