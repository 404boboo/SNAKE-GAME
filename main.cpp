#include "game.hpp"
#include "Main_menu.h"
#include "endMenu.hpp"
#include <iostream>
#include <fstream>

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
        //window.setVerticalSyncEnabled(true);
        window.setActive(true);
        sf::Texture background;
        background.loadFromFile("playbackground.jpg");
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

                // Checking if file is empty if the player was playing for the first time.
                int scoreNumber;
                int highScore;
                ifstream read("highscore.txt");
                if(!read) return 0;
                bool isEmpty = read.peek() == EOF;
                //
                string line;
                std::fstream checkScore;
                checkScore.open("highscore.txt", std::ios::in | std::ios::out);
                if (checkScore.is_open()) {
                    if(isEmpty){ // if file empty then just add the lastest score
                        checkScore << game.getScore();
                    }
                    else{ // if there's a score then write it to scoreNumber
                        while(!checkScore.eof())
                            checkScore >> scoreNumber;

                    }
                }
                if(scoreNumber < game.getScore()){
                    highScore = game.getScore();
                    std::ofstream hscore("highscore.txt", std::ofstream::trunc);

                       hscore << game.getScore();


                       hscore.close();
                }
                else
                    highScore = scoreNumber;

                // SCORE AT THE END OF GAME

                sf::Font font;
                if (!font.loadFromFile("arial.ttf")){
                    std::cout << "FONT NOT LOADDED" <<std::endl;
                }
                sf::Text score;
                score.setFont(font);
                score.setColor(sf::Color::Red);
                std::string scoreLabel = "SCORE: ";
                scoreLabel += to_string(game.getScore());
                score.setString(scoreLabel);
                score.setCharacterSize(50);
                score.setPosition(sf::Vector2f((WIDTH * BLOCK_SIZE) / 2.7 , (HEIGHT * BLOCK_SIZE) / 2.2));

                sf::Text highScoreLabel;
                highScoreLabel.setFont(font);
                highScoreLabel.setColor(sf::Color::Black);
                std::string hscoreLabel = "High Score: ";
                hscoreLabel += to_string(highScore);
                highScoreLabel.setString(hscoreLabel);
                highScoreLabel.setCharacterSize(50);
                highScoreLabel.setPosition((WIDTH * BLOCK_SIZE) / 3.4 , (HEIGHT * BLOCK_SIZE) / 1.8);

                End_menu endMenu(50, 370);

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::KeyReleased)
                    {

                        if (event.key.code == sf::Keyboard::Return) // enter
                        {


                            if (endMenu.endMenuPressed() == 0)
                            {
                                window.close();
                                buttonNumber = 1;
                            }
                        }


                    }

                }




                // Draw gameover screen

                window.clear(sf::Color::Green);
                window.draw(grassMap);
                window.draw(score);
                window.draw(highScoreLabel);
                endMenu.draw(window);
                window.display();

                // window.close();
                // break;

            }
            else {

                // Draw
                window.clear(sf::Color::Green);
                window.draw(grassMap); // background
                game.draw(&window, (float)clock.getElapsedTime().asMilliseconds()/game.getSnakeSpeed());
                // game.draw(&window, TPB);
            }

            window.display();



            }
    }

            else    // Exit
                mainWindow.close();


    return 0;
}
