#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class ObstacleSprite : public sf::Drawable {

    private:
    public:
        sf::Sprite* sprite;
        sf::Texture* texture;
        std::string fileName;
        sf::Uint8* mask; // Used for collision detection
        ObstacleSprite();
        ObstacleSprite(int blockSize, float windowWidth, float windowHeight);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setResource(const string resourceFilePath);
        void setSpritePosition(float x, float y, int width, int height);
};
