#include "Victim.hpp"


VictimSprite::VictimSprite() {}

VictimSprite::VictimSprite(int blockSize, float windowWidth, float windowHeight) {
    texture = new sf::Texture();    
    texture->loadFromFile("assets/victim/rat.png");
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setScale(0.08, 0.08);
}

void VictimSprite::setSpritePosition(float x, float y, int width, int height) {
    // if(x / )
    sprite->setPosition(x, y);
}

void VictimSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*sprite, states);
}