#pragma once

#include "pancake/pancake.hpp"

class TitleComponent : public Component {
   
    public:
        TitleComponent();
        void update(float dt) override;    
        
};