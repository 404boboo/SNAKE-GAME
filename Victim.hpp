#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class VictimSprite : public sf::Drawable {
    
    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
    
    public:
        VictimSprite();
        VictimSprite(int blockSize, float windowWidth, float windowHeight);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setResource(const string resourceFilePath);
        // void setFillColor(sf::Color color);
        void setSpritePosition(float x, float y, int width, int height);
};
