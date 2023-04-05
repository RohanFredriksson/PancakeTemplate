#include "title.hpp"

Component* TitleComponent::create() {
    return new TitleComponent();
}

TitleComponent::TitleComponent() : Component("TitleComponent") {

}

void TitleComponent::update(float dt) {

    if (MouseListener::isMouseBeginDown(GLFW_MOUSE_BUTTON_LEFT)) {
        
        Component* c = this->getEntity()->getComponentByType("AudioPlayer");
        if (c == NULL) {return;}
        
        AudioPlayer* a = dynamic_cast<AudioPlayer*>(c);
        a->play();

    }

}