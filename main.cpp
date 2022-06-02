#include "game.hpp"

// Size of each block
#define BLOCK_SIZE 50
#define SNAKE_SIZE 25
// Windows size in terms of blocks
#define WIDTH 20
#define HEIGHT 10

// Speed of snake
// time (miliseconds) per block
#define TPB 120.f

int main() {
    // Main window
    sf::RenderWindow window(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE), "Snake Game");
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    sf::Texture background;
    background.loadFromFile("grass.jpg");
    background.setSmooth(true);
    background.setRepeated(true);
    sf::Sprite grassMap(background);
    grassMap.setTextureRect({0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE});
    grassMap.setScale(WIDTH * BLOCK_SIZE / background.getSize().x, HEIGHT * BLOCK_SIZE / background.getSize().y);
    // SFML Clock
    sf::Clock clock;

    // Game vars
    Game game(WIDTH, HEIGHT, BLOCK_SIZE, SNAKE_SIZE);
    GameDirection dir = GameDirection::Stay;
    GameDirection dirCur = GameDirection::Stay;

    // Loop
    while (window.isOpen()) {

        // Handle all events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Right && dirCur != GameDirection::Left)
                        dir = GameDirection::Right;
                    if (event.key.code == sf::Keyboard::Left && dirCur != GameDirection::Right)
                        dir = GameDirection::Left;
                    if (event.key.code == sf::Keyboard::Up && dirCur != GameDirection::Down)
                        dir = GameDirection::Up;
                    if (event.key.code == sf::Keyboard::Down && dirCur != GameDirection::Up)
                        dir = GameDirection::Down;
                    break;
            }
        }

        // Get time
        int animationState = clock.getElapsedTime().asMilliseconds();
        if (animationState >= TPB) {
            clock.restart();
            dirCur = dir;
            game.move(dirCur);
        }

        // Game over
        if (game.gameOver) {
            window.clear(sf::Color::Green);
            window.draw(grassMap); // game over screen, for now it's just normal background -- to be updated
            // window.close();
            // break;
        } else {
            // Draw
            window.clear(sf::Color::Green);
            window.draw(grassMap); // background
            game.draw(&window, (float)clock.getElapsedTime().asMilliseconds()/TPB);
            // game.draw(&window, TPB);
        }

        window.display();
    }

    return 0;
}
