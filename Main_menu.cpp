#include "Main_menu.h"
#include <iostream>


Main_menu::Main_menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf")){}

    highScore.open("highscore.txt", std::ios::in);
    if (highScore.is_open())
        highScore >> score;
    // Play
    mainMenu[0].setFont(font);
    mainMenu[0].setColor(sf::Color::Blue);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(50);
    mainMenu[0].setPosition(sf::Vector2f(width / 2 , height / (Max_main_menu + 1)));
    // EXIT
    mainMenu[1].setFont(font);
    mainMenu[1].setColor(sf::Color::White);
    mainMenu[1].setString("Exit");
    mainMenu[1].setCharacterSize(50);
    mainMenu[1].setPosition(sf::Vector2f(width / 2 , height / (Max_main_menu + 1) * 2));

    // SCORE


    mainMenu[2].setFont(font);
    mainMenu[2].setColor(sf::Color::Black);
    scoreLabel += std::to_string(score);
    mainMenu[2].setString(scoreLabel);
    mainMenu[2].setCharacterSize(30);
    mainMenu[2].setPosition(sf::Vector2f(width / 2 , height / (Max_main_menu + 1) * 5));





    mainMenuSelected = 0;  // start from index zero

}




Main_menu::~Main_menu()
{
}


// Function of drawing main menu
void Main_menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainMenu[i]);
    }
}

// Function of moving up
void Main_menu::moveUp()
{
    if (mainMenuSelected - 1 >= -1) // check if not on the first item (play)

    {

        mainMenu[mainMenuSelected].setColor(sf::Color::White);  // change the pervious item's color

        mainMenuSelected--;  // move to the upper item
        if (mainMenuSelected == -1)
        {
            mainMenuSelected = 1;
        }
        mainMenu[mainMenuSelected].setColor(sf::Color::Blue); // change the new item's color
    }
}

// Function of moving down
void Main_menu::moveDown()
{
    if (mainMenuSelected + 1 <= Max_main_menu) // check if not on the last item (exit)

    {
        mainMenu[mainMenuSelected].setColor(sf::Color::White);  // change the pervious item's color

        mainMenuSelected++;  // move to the lower item
        if (mainMenuSelected == 2)
        {
            mainMenuSelected = 0;
        }
        mainMenu[mainMenuSelected].setColor(sf::Color::Blue);           // change the new item's color

    }
}
