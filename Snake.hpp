#include <SFML/Graphics.hpp>
// #include "game.hpp";

// Linked list of 2D vectors
struct VectorList {
    sf::Vector2f vec;
    VectorList *next;
};

class Snake {

    private:
        sf::RectangleShape headShape;
        sf::RectangleShape stomicShape;
        sf::RectangleShape tailShape;

    public:
        Snake(sf::Vector2f initialPosition);   
        // virtual ~Snake();
        void setColor(sf::Color color);
        // void setPosition(Vector2f Vector);
        void render(sf::RenderWindow* window, sf::Vector2f position);
        void renderHead(sf::RenderWindow* window, sf::Vector2f headPosition);
        void renderStomic(sf::RenderWindow* window, sf::Vector2f stomicPosition);
        void renderTail(sf::RenderWindow* window, sf::Vector2f tailPosition);
        void setHead(sf::RectangleShape pHead);
        void setStomic(sf::RectangleShape pStomic);
        void setTail(sf::RectangleShape pTail);
};
