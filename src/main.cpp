#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate(sf::RenderWindow &window);

GUI::Button buttons[10];


int main()
{
    sf::RenderWindow window(sf::VideoMode(630, 735), "Calculator");

    appInit();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "LMB Pressed" << std::endl;
                }
            }
        }

        window.clear();
        appDraw(window);
        window.display(); 
        appUpdate(window);
    }

    return 0;
}

void appInit()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(7 + j - (i * 3));
            buttons[j + (3 * i)].setPosition(sf::Vector2f((105.f * j) + 105.f, 210.f + (105.f * i)));
            buttons[j + (3 * i)].setSize(sf::Vector2f(100.f, 100.f));
            buttons[j + (3 * i)].setText(str, sf::Color::Black);
        }
    }
    buttons[9].setPosition(sf::Vector2f(210.f, 525.f));
    buttons[9].setSize(sf::Vector2f(100.f, 100.f));
    buttons[9].setText("0", sf::Color::Black);
}

void appDraw(sf::RenderWindow &window)
{
    for (int i = 0; i < 10; i++)
    {
        buttons[i].draw(window);
    }
}

void appUpdate(sf::RenderWindow &window)
{
    for (int i = 0; i < 10; i++)
    {
        buttons[i].update(window);
    }
}