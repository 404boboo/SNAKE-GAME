#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Victim.hpp"
#include "Obstacle.hpp"
#include "CollisionDetection.h"


// Directions
enum class GameDirection { Right, Left, Up, Down, Stay };

// Game controller
class Game
{
private:
    const int OBSTACLES_COUNT = 5;
    int width, height;
    float blockSize;
    float snakeSize;
    float snakeSpeed; // for the speed pickup
    int scoreCounter = 0;
    VectorList *snake;
    VectorList *head;
    // GameDirection currentDirection; // Will be used to identify direction
    bool turning; // Will be used to identify positions in vector list that needs to be showing turning
    sf::Vector2f prevHeadPos;
    sf::Vector2f prevTailPos;
    sf::Vector2f foodPos;
    VictimSprite victim;
    VectorList *obstacles;
    ObstacleList *obstacleList;
    ObstacleSprite tempObstacle;
    bool obstaclesExist = false;

    sf::Vector2f randPos();
    void genFood();
    sf::Vector2f mul(sf::Vector2f a, float b);
    sf::Vector2f moveForwardTo(sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float w);
public:
    bool gameOver;
    Game(int width, int height, float blockSize, float snakeSize, float initialSpeed);
    void move(GameDirection dir);
    void draw(sf::RenderWindow *window, float state);
    void increaseSnakeSpeed();
    int getScore();
    float getSnakeSpeed();
};
