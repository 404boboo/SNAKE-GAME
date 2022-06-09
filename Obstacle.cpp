#include "ObstacleSprite.hpp"

ObstacleSprite::ObstacleSprite(){}

ObstacleSprite::ObstacleSprite(int blockSize, float windowWidth, float windowHeight) {
    texture = new sf::Texture();    
    texture->loadFromFile("tree.png");
    this->fileName = "tree.png";
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    // sprite->setTextureRect(sf::IntRect(0, 0, 300, 300));
    // sprite->setOrigin(50, 50);
    // sprite->setOrigin(0, 0);
    sprite->setScale(0.05, 0.05);
    // sprite->setTextureRect({0, 0, windowWidth, windowHeight});
}


void ObstacleSprite::setSpritePosition(float x, float y, int width, int height) {
    // if(x / )
    sprite->setPosition(x, y);
}

void ObstacleSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // std::cout << "Obstacle X: " << sprite->getPosition().x << ", Obstacle Y: " << sprite->getPosition().y << std::endl;
    target.draw(*sprite, states);
}
