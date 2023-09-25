#pragma once


#include <vector>
#include <glm/glm.hpp>

#include "pancake/pancake.hpp"

namespace SnakeDirection {
    const glm::ivec2 UP    = glm::ivec2( 0,  1);
    const glm::ivec2 DOWN  = glm::ivec2( 0, -1);
    const glm::ivec2 LEFT  = glm::ivec2(-1,  0);
    const glm::ivec2 RIGHT = glm::ivec2( 1,  0);
    
}

class Snake : public Pancake::Component {
   
    private: 

        std::vector<glm::ivec2> body;
        std::vector<glm::ivec2> inputs;
        std::vector<Pancake::SpriteRenderer*> sprites;
        
        float progress;
        float speed;
        glm::ivec2 direction;

        bool alive;
        bool dirty;

    public:

        Snake();
        void start() override;
        void update(float dt) override;
        
};

REGISTER(Pancake::Component, Snake);