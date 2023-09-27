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
        std::array<glm::ivec2, 2> getBounds();

    public:

        Snake();
        void start() override;
        void update(float dt) override;

};

REGISTER(Pancake::Component, Snake);