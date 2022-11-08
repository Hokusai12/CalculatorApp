#include <SFML/Graphics.hpp>
#include "GUI.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Calculator");
    GUI::Button button(sf::Vector2f(250.f, 350.f), sf::Vector2f(100.f, 100.f), "Booty");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        button.draw(window);
        window.display(); 
    }

    return 0;
}