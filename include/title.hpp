#pragma once

#include "pancake/pancake.hpp"

class TitleComponent : public MouseDown, public Component {
   
    public:
        static Component* create();
        TitleComponent();
        void onMouseDown() override;    
        
};