#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>


class End_menu
{
public:
    End_menu(float width, float hight);


    void draw(sf::RenderWindow &window);

    int endMenuPressed()
    {
        return endMenuSelected;;
    }

    ~End_menu();


private:
    int endMenuSelected;
    std::fstream highScore;
    int score;
    std::string scoreLabel = "High Score: ";
    sf::Font font;
    sf::Text endMenu[1];
};
