#pragma once

#include "pancake/pancake.hpp"
using namespace Pancake;

class TitleComponent : public Component {
   
    public:
        TitleComponent();
        void update(float dt) override;    
        
};

REGISTER(Component, TitleComponent);