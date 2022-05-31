#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Victim.hpp"
#include "Obstacle.hpp"

// Directions
enum class GameDirection { Right, Left, Up, Down, Stay };

// Game controller
class Game
{
private:
    int width, height;
    float blockSize;
    float snakeSize;
    VectorList *snake;
    VectorList *head;
    // GameDirection currentDirection; // Will be used to identify direction
    bool turning; // Will be used to identify positions in vector list that needs to be showing turning
    sf::Vector2f foodPos;
    sf::Vector2f prevHeadPos;
    sf::Vector2f prevTailPos;
    // sf::Shape *foodSprite;
    
    // Snake snakeShape;

    sf::Vector2f randPos();
    void genFood();
    sf::Vector2f mul(sf::Vector2f a, float b);
    sf::Vector2f moveForwardTo(sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float w);
public:
    bool gameOver;
    Game(int width, int height, float blockSize, float snakeSize);
    void move(GameDirection dir);
    void draw(sf::RenderWindow *window, float state);
};
