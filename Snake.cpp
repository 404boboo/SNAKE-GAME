#include "Snake.hpp"


Snake::Snake(sf::Vector2f initialPosition) {
    // c_window = &window;
    sf::RectangleShape head(initialPosition);
    head.setFillColor(sf::Color::Blue);
    sf::RectangleShape stomic(initialPosition);
    stomic.setFillColor(sf::Color::Red);
    sf::RectangleShape tail(initialPosition);
    tailShape.setFillColor(sf::Color::Black);
    headShape = head;
    stomicShape = stomic;
    tailShape = tail;

}


void Snake::renderHead(sf::RenderWindow* window, sf::Vector2f headPosition) {
    // headSprite->setPosition(headPosition);
    headShape.setFillColor(sf::Color::Blue);
    headShape.setPosition(headPosition);
    window->draw(headShape);
}

void Snake::renderStomic(sf::RenderWindow* window, sf::Vector2f stomicPosition) {
    // stomicSprite->setPosition(stomicPosition);
    // stomic.setFillColor(sf::Color::Red);
    stomicShape.setFillColor(sf::Color::Red);
    stomicShape.setPosition(stomicPosition);
    window->draw(stomicShape);
}

void Snake::renderTail(sf::RenderWindow* window, sf::Vector2f tailPosition) {
    // tailSprite->setPosition(tailPosition);
    // tailShape.setFillColor(sf::Color::Black);
    tailShape.setFillColor(sf::Color::Red);
    tailShape.setPosition(tailPosition);
    window->draw(tailShape);
}

