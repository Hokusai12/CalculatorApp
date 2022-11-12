#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate();

GUI::Button buttons[10];


int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 700), "Calculator");

    appInit();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        appDraw(window);
        window.display(); 
    }

    return 0;
}

void appInit()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(j + (i * 3));
            GUI::Button button(sf::Vector2f(100.f * j, 200.f + (100.f * i)), sf::Vector2f(100.f, 100.f), str);
            buttons[j + (3 * i)] = button;
        }
    }
}

void appDraw(sf::RenderWindow &window)
{
    for (int i = 0; i < 9; i++)
    {
        buttons[i].draw(window);
    }
}