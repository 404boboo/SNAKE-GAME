#include "game.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Game::Game(int width, int height, float blockSize, float snakeSize) {
    srand(time(NULL));

    // Init vars
    this->width = width;
    this->height = height;
    this->blockSize = blockSize;
    this->snakeSize= snakeSize;
    gameOver = false; // will change this to true when game is over

    // Initialize snake linked list
    snake = new VectorList();
    snake->vec = randPos();
    snake->next = NULL;
    head = snake;
    prevHeadPos = snake->vec;
    prevTailPos = snake->vec;

    

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

    // Just move and check overlaps
    else {
        VectorList *temp = snake;
        while (temp->next) {
            // if (temp->vec == head->vec) {
            //     gameOver = true;
            // }
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

}

sf::Vector2f Game::randPos() {
    return sf::Vector2f(rand() % width, rand() % height);
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
