#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "Button.h"
#include "TextArea.h"
#include "Calculation.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate(sf::RenderWindow &window);



sf::Font appFont;
GUI::Button numButtons[10];
GUI::Button opButtons[5];
GUI::Button clrButton;
GUI::TextArea equationDisplay(sf::Vector2f(5.f, 10.f), sf::Vector2f(490.f, 105.f), "");

bool solveTime = false;
bool isSolved = false;
std::string equation = "";
std::vector<char> operators;
std::vector<double> numbers;


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 640), "Calculator");
    sf::RectangleShape background(sf::Vector2f(500.f, 640.f));
    background.setFillColor(sf::Color::Color(100, 100, 100));

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
                    for (int i = 0; i < 10; i++)
                    {
                        if (numButtons[i].isActive())
                        {
                            equation += numButtons[i].getTextString().toAnsiString();
                            equationDisplay.concatText(numButtons[i].getTextString().toAnsiString());
                        }
                    }
                    for (int i = 0; i < 5; i++)
                    {
                        if (opButtons[i].isActive())
                        {
                            numbers.emplace_back(equation);
                            operators.emplace_back(opButtons[i].getTextString().toAnsiString()[0]);
                            equationDisplay.concatText(opButtons[i].getTextString().toAnsiString()[0]);

                            if(operators.f)

                            if (opButtons[i].getTextString().toAnsiString() == "=")
                            {
                                operators.pop_back();
                                solveTime = true;
                                i = 5;
                            }
                        }
                    }
                    if (clrButton.isActive())
                    {
                        equationDisplay.clearText();
                        numbers.clear();
                        operators.clear();
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        appDraw(window);
        window.display(); 
        appUpdate(window);
    }

    return 0;
}

void appInit()
{
    if (!appFont.loadFromFile("assets/fonts/ArialTh.ttf"))
        std::cerr << "Couldn't load font file!" << std::endl;

    clrButton = new GUI::Button(sf::Vector2f(70.f, 465.f), sf::Vector2f(100.f, 100.f), "CLR", appFont);

    for (int i = 0; i < 4; i++)
    {
        std::string op;
        switch(i)
        {
        case 0:
            op = "/";
            break;
        case 1:
            op = "*";
            break;
        case 2:
            op = "-";
            break;
        case 3:
            op = "+";
            break;
        default: 
            op = "";
            break;
        }
        opButtons[i] = new GUI::Button(sf::Vector2f(385.f, (150.f + (i * 105.f))), sf::Vector2f(100.f, 100.f), op, appFont);
        opButtons[i].setBoxColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    }

    opButtons[4] = new GUI::Button(sf::Vector2f(280.f, 465.f), sf::Vector2f(100.f, 100.f), "=", appFont);
    opButtons[4].setBoxColor(sf::Color::Color(180, 180, 180), sf::Color::Black);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(7 + j - (i * 3));
            numButtons[j + (3 * i)] = new GUI::Button(
                sf::Vector2f((105.f * j) + 70.f, 150.f + (105.f * i)),
                sf::Vector2f(100.f, 100.f),
                str,
                appFont);
        }
    }
    numButtons[9] = new GUI::Button(sf::Vector2f(175.f, 465.f), sf::Vector2f(100.f, 100.f), "0", appFont);
}

void appDraw(sf::RenderWindow &window)
{
    for (int i = 0; i < 10; i++)
    {
        numButtons[i].draw(window);
    }
    for (int i = 0; i < 5; i++)
    {
        opButtons[i].draw(window);
    }
    equationDisplay.draw(window);
    clrButton.draw(window);
}

void appUpdate(sf::RenderWindow &window)
{
    if (!solveTime)
    {
        for (int i = 0; i < 10; i++)
        {
            numButtons[i].update(window);
        }
        for (int i = 0; i < 5; i++)
        {
            opButtons[i].update(window);
        }
        clrButton.update(window);
    }
    else if (solveTime)
    {
        double solution = Calc::solveEquation(operators, numbers);
        if (solution - std::trunc(solution) > 0)
        {
            equationDisplay.setText(std::to_string(solution));
        }
        else
        {
            equationDisplay.setText(std::to_string((int)solution));
        }
        operators.clear();
        solveTime = false;
        isSolved = true;
    }
}

