#include "game.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>


Game::Game(int width, int height, float blockSize, float snakeSize, float initialSpeed) {
    srand(time(NULL));

    // Init vars
    this->width = width;
    this->height = height;
    this->blockSize = blockSize;
    this->snakeSize= snakeSize;
    this->snakeSpeed = initialSpeed;
    gameOver = false; // will change this to true when game is over

    // Initialize victim
    VictimSprite c_victim(blockSize, width, height);
    victim = c_victim;


    // victim.setFillColor(sf::Color::Red);
    genFood();

    // Initialize snake linked list
    snake = new VectorList();
    snake->vec = randPos();
    snake->next = NULL;
    head = snake;
    prevHeadPos = snake->vec;
    prevTailPos = snake->vec;

    // Initialize and draw obstacles
     int current = 0;
     VectorList* tempObstacle = nullptr;
     ObstacleList* cObstaclesList = nullptr;
     ObstacleList* tempObstacleList = nullptr;
     while(current < OBSTACLES_COUNT) {
         obstacles = new VectorList();
         cObstaclesList = new ObstacleList();
         obstacles->vec = randPos();
         obstacles->next = tempObstacle;
         tempObstacle = obstacles;
         ObstacleSprite obstacle(blockSize, width, height);
         obstacle.setSpritePosition(obstacles->vec.x * blockSize, obstacles->vec.y * blockSize, width, height);
         cObstaclesList->obstacle = obstacle;
         cObstaclesList->next = tempObstacleList;
         tempObstacleList = cObstaclesList;
         current++;
    }
    obstacleList = cObstaclesList;

    

}

void Game::move(GameDirection dir) {
    prevHeadPos = head->vec;
    prevTailPos = snake->vec;

    sf::Vector2f newPos = head->vec;
    switch (dir)
    {
    case GameDirection::Right:
        newPos.x += 1;
        break;
    case GameDirection::Left:
        newPos.x -= 1;
        break;
    case GameDirection::Up:
        newPos.y -= 1;
        break;
    case GameDirection::Down:
        newPos.y += 1;
        break;
    }
    ////////////////////// Check hitting obstacle Start ////////////////////
    ObstacleList* tempPtr = obstacleList;

    while(tempPtr != nullptr) {
        ObstacleSprite obstacle = tempPtr->obstacle;

        // std::cout << "X: " << newPos.x * blockSize << std::endl;
        // Check collision
        sf::Uint8* mask = Collision::createTextureAndBitmask(obstacle.sprite->getTexture(), obstacle.fileName);
        if(Collision::pixelCollideVector(obstacle.sprite, mask, blockSize, newPos, 0)) {
            gameOver = true;
        }

        tempPtr = tempPtr->next;
    }

    //////////////////////// Check hitting obstacle End ////////////////////


    if (newPos.x < -2) {
        newPos.x = (width)+2;
    }

    if(newPos.x > (width)+2) {
        newPos.x = -2;
    }

    if(newPos.y < -2) {
        newPos.y = (height)+2;
    }

    if(newPos.y > (height)+2) {
        newPos.y = -2;
    }

    // Eat food
    bool HARD = false; // FOR MENU MODE
    int mode = 5;
    if (HARD){
        mode = 3;
    }

    if (newPos.x == foodPos.x && newPos.y == foodPos.y) {
            head->next = new VectorList();
            head = head->next;
            head->next = NULL;
            head->vec = newPos;
            scoreCounter+=10; // increasing the score everytime the player eats a victim
            if(scoreCounter % mode == 0){ // checking if the score increased by 3 so we can increase the snake's speed everytime the score increases by 3
              increaseSnakeSpeed();
            }
            genFood();
        }
    // Just move and check overlaps
    else {
        VectorList *temp = snake;
        while (temp->next) {
            if (temp->vec == head->vec)
                gameOver = true;
            temp->vec = temp->next->vec;
            temp = temp->next;
        }
        head->vec = newPos;
    }
}

void Game::draw(sf::RenderWindow* window, float state) {
    // Normolize state
    if (state > 1)
        state = 1;

    // Block snake
    sf::Color headColor = sf::Color::Blue;
    sf::Color stomicColor = sf::Color::Red;
    sf::Color tailColor = sf::Color::Black;

    // Create a snake and set initial position
    Snake currentSnake(sf::Vector2f(snakeSize, snakeSize));

    // Animated head
    currentSnake.renderHead(window, mul(lerp(prevHeadPos, head->vec, state), blockSize));

    // debugging position

    // int x = block.getPosition().x;
    // int y = block.getPosition().y;
    // std::cout << "x: " << std::to_string(x) << ", y: " << std::to_string(y) << std::endl;

    // // Animated tail
    currentSnake.renderTail(window, mul(lerp(prevTailPos, snake->vec, state), blockSize));

    // Animated stomic
    VectorList *temp = snake;
    VectorList *prev = snake;
    while (temp->next) {
        currentSnake.renderStomic(window, mul(temp->vec, blockSize));
        temp = temp->next;
    }
    // Victim / Food
        window->draw(victim);
        VectorList* tempObstacles = obstacles;
        // Loop through vector list of obstacles*
        int obstacleCount = 0;
        while(tempObstacles != nullptr) {
            ObstacleSprite obstacle(snakeSize, width, height);
            obstacle.setSpritePosition(tempObstacles->vec.x * blockSize, tempObstacles->vec.y * blockSize, width, height);
            tempObstacle = obstacle;
            window->draw(obstacle);
            tempObstacles = tempObstacles->next;
            obstacleCount++;
        }
}

sf::Vector2f Game::randPos() {
    return sf::Vector2f(rand() % width, rand() % height);
}

void Game::genFood() {
    foodPos = randPos();
    victim.setSpritePosition(foodPos.x * blockSize, foodPos.y * blockSize, width, height);
}


void Game::increaseSnakeSpeed(){
    this->snakeSpeed -= 10;
}

float Game::getSnakeSpeed(){
    return this->snakeSpeed;
}

sf::Vector2f Game::moveForwardTo(sf::Vector2f a, sf::Vector2f b) {
    if (a.x < b.x)
        a.x += 1;
    else if (a.x > b.x)
        a.x -= 1;
    else if (a.y < b.y)
        a.y += 1;
    else if (a.y > b.y)
        a.y -= 1;
    return a;
}

sf::Vector2f Game::mul(sf::Vector2f a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

sf::Vector2f Game::lerp(sf::Vector2f a, sf::Vector2f b, float w) {
    a.x += (b.x - a.x) * w;
    a.y += (b.y - a.y) * w;
    return a;
}

int Game::getScore(){
    return scoreCounter;
}


