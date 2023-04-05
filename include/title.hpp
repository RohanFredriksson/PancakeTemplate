#pragma once

#include "pancake/pancake.hpp"

class TitleComponent : public Component {
   
    public:
        static Component* create();
        TitleComponent();
        void update(float dt) override;    
        
};