#include "game.hpp"
#include "Main_menu.h"

// Size of each block
#define BLOCK_SIZE 50
#define SNAKE_SIZE 25
// Windows size in terms of blocks
#define WIDTH 20
#define HEIGHT 10

// Speed of snake
// time (miliseconds) per block
#define TPB 180.f
int buttonNumber;
bool HARD = false;
int main() {
    // Main window
    sf::RenderWindow mainWindow(sf::VideoMode(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE)), "SFML_Make_Menu", sf::Style::Close);
    sf::Texture menuBackground;
    menuBackground.loadFromFile("menu.jpg");
    menuBackground.setSmooth(true);
    sf::Sprite menubg(menuBackground);
    menubg.setTextureRect({0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE});
    menubg.setScale(1,1);
    Main_menu menu(50, 370); // Placing it on the left of the screen idk why but it looks better on left.

    while (mainWindow.isOpen())
            {
                sf::Event event;
                while (mainWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        mainWindow.close();
                    if (event.type == sf::Event::KeyReleased)
                    {
                        if (event.key.code == sf::Keyboard::Up)
                        {
                            menu.moveUp();
                            break;
                        }
                        if (event.key.code == sf::Keyboard::Down)
                        {
                            menu.moveDown();
                            break;
                        }

                        // choose button
                        if (event.key.code == sf::Keyboard::Return) // enter
                        {

                            if (menu.mainMenuPressed() == 0)
                            {
                                mainWindow.close();
                                buttonNumber = 0;
                            }
                            if (menu.mainMenuPressed() == 1)
                            {
                                mainWindow.close();
                                buttonNumber = 1;
                            }
                            if (menu.mainMenuPressed() == 2)
                            {
                                mainWindow.close();
                                buttonNumber = 2;
                            }
                        }


                    }

                }
                mainWindow.clear();
                mainWindow.draw(menubg);
                menu.draw(mainWindow);

                mainWindow.display();
            }

    if (buttonNumber == 0)  // buttonNumber 0 - PLAY
            {

        sf::RenderWindow window(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE), "Snake Game");
        window.setVerticalSyncEnabled(true);
        window.setActive(true);
        sf::Texture background;
        background.loadFromFile("image.png");
        background.setSmooth(true);
        background.setRepeated(true);
        sf::Sprite grassMap(background);
        grassMap.setTextureRect({0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE});
        grassMap.setScale(1,1);



        // SFML Clock
        sf::Clock clock;

        // Game vars
        Game game(WIDTH, HEIGHT, BLOCK_SIZE, SNAKE_SIZE, TPB);
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
            if (animationState >= game.getSnakeSpeed()) {
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
                game.draw(&window, (float)clock.getElapsedTime().asMilliseconds()/game.getSnakeSpeed());
                // game.draw(&window, TPB);
            }

            window.display();



            }
    }

            if (buttonNumber == 1)
            {
                // Exit

                mainWindow.close();

            }




    return 0;
}
