#include "pancake/pancake.hpp"
#include "title.hpp"

using glm::vec2;
using glm::vec4;

void TitleInit(Scene* scene) {

    Spritesheet::load("assets/textures/faces.png");

    Entity* entity;
    Texture* texture;
    Sprite* sprite;
    SpriteRenderer* spriterenderer;
    Box* box;
    Circle* circle;
    Rigidbody* rigidbody;
    TextRenderer* textrenderer;
    AudioPlayer* audioplayer;
    TitleComponent* titlecomponent;

    // BOX 1
    entity = new Entity(vec2(-4.5f, 5.0f), vec2(1.0f, 1.0f), 0.0f);

    sprite = SpritePool::get("armaan");
    spriterenderer = new SpriteRenderer();
    spriterenderer->setSprite(sprite);
    entity->addComponent(spriterenderer);

    rigidbody = new Rigidbody();
    rigidbody->setRestitution(0.2f);
    rigidbody->setFriction(0.0f);
    rigidbody->setVelocity(vec2(1.0f, 0.0f));
    rigidbody->setFixedOrientation(true);

    box = new Box();
    box->setMass(1.0f);
    box->setSize(vec2(1.0f, 1.0f));
    rigidbody->addCollider(box);
    entity->addComponent(rigidbody);

    audioplayer = new AudioPlayer();
    audioplayer->setAudioWave(AudioPool::get("assets/audio/click.mp3"));
    entity->addComponent(audioplayer);

    titlecomponent = new TitleComponent();
    entity->addComponent(titlecomponent);
        
    scene->addEntity(entity);

    // BOX 2
    entity = new Entity(vec2(0.0f, 0.0f), vec2(11.0f, 1.0f), 0.0f);
    
    sprite = SpritePool::get("ainsley");
    spriterenderer = new SpriteRenderer();
    spriterenderer->setSprite(sprite);
    
    rigidbody = new Rigidbody();
    rigidbody->setRestitution(1.0f);
    rigidbody->setFriction(0.0f);
    
    box = new Box();
    box->setMass(0.0f);
    box->setSize(vec2(11.0f, 1.0f));
    rigidbody->addCollider(box);

    entity->addComponent(spriterenderer);
    entity->addComponent(rigidbody);
    scene->addEntity(entity);

}

int main(int argc, char* argv[]) {
    return Engine::run("Title", "saves/save.scene");
    //return Engine::run("Title", TitleInit);
}