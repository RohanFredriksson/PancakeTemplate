#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>

#include "pancake/pancake.hpp"

class SnakeMap : public Pancake::Component {
   
    private: 

        std::vector<Pancake::SpriteRenderer*> sprites;
        std::array<glm::ivec2, 2> bounds;
        bool dirty;

    public:

        SnakeMap();
        void update(float dt) override;
        void setBounds(glm::ivec2 min, glm::ivec2 max);

        std::array<glm::ivec2, 2> getBounds();
        
};

REGISTER(Pancake::Component, SnakeMap);