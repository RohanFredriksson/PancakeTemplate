#include "pancake/pancake.hpp"

class ArrowHint : public Pancake::TransformableComponent {
   
    private: 

        std::vector<Pancake::SpriteRenderer*> sprites;

    public:

        ArrowHint();
        void start() override;
        void update(float dt) override;

};

REGISTER(Pancake::Component, ArrowHint);