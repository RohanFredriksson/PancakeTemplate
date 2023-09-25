#pragma once


#include <vector>
#include <glm/glm.hpp>

#include "pancake/pancake.hpp"

class Snake : public Pancake::Component {
   
    private: 

        std::vector<glm::ivec2> body;
        std::vector<glm::ivec2> inputs;
        std::vector<Pancake::SpriteRenderer*> bodySprites;
        std::vector<Pancake::SpriteRenderer*> endSprites;
        
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