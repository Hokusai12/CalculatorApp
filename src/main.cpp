#include <SFML/Graphics.hpp>
#include <vector>
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
    GUI::Button button(sf::Vector2f(150.f, 250.f), sf::Vector2f(100.f, 100.f), "9");
    buttons[0] = button;
}

void appDraw(sf::RenderWindow &window)
{
    buttons[0].draw(window);
}