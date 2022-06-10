#include "endMenu.hpp"
#include <iostream>


End_menu::End_menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf")){}

    highScore.open("highscore.txt", std::ios::in);
    if (highScore.is_open())
        highScore >> score;
    // EXIT
    endMenu[0].setFont(font);
    endMenu[0].setColor(sf::Color::Blue);
    endMenu[0].setString("PRESS ENTER TO EXIT");
    endMenu[0].setCharacterSize(50);
    endMenu[0].setPosition(sf::Vector2f(width * 4 , height / (3)));

    endMenuSelected = 0;

}




End_menu::~End_menu()
{
}


// Function of drawing main menu
void End_menu::draw(sf::RenderWindow &window)
{

        window.draw(endMenu[0]);

}
