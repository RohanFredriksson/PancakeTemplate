#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>

#include "pancake/pancake.hpp"

class Snake : public Pancake::Component {
   
    private: 

        std::vector<glm::ivec2> bodies;
        std::vector<glm::ivec2> inputs;
        std::vector<Pancake::SpriteRenderer*> sprites; // Never deleted at runtime.
        std::vector<Pancake::SpriteRenderer*> dynamics; // Dynamic sprites.

        std::array<glm::ivec2, 2> bounds;
        glm::ivec2 food;
        
        bool alive;
        bool consumed;
        float progress;
        float speed;
        glm::ivec2 direction;
        
        void head();
        void tail();
        void body(bool changed);
        void consume();

    public:

        Snake();
        void start() override;
        void update(float dt) override;
        void setBounds(glm::ivec2 min, glm::ivec2 max);

};

REGISTER(Pancake::Component, Snake);