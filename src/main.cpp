#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include "Button.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate(sf::RenderWindow &window);
bool solveEquation(std::string &equation);
double addNums(double a, double b) { return a + b; }
double subNums(double a, double b) { return a - b; }
double multNums(double a, double b) { return a * b; }
double divNums(double a, double b) { return a / b; }


GUI::Button numButtons[10];
GUI::Button opButtons[5];

bool solveTime = false;
std::string equation = "";


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
                    for (int i = 0; i < 10; i++)
                    {
                        if (numButtons[i].isActive())
                        {
                            equation += numButtons[i].getTextString().toAnsiString();
                        }
                    }
                    for (int i = 0; i < 5; i++)
                    {
                        if (opButtons[i].isActive())
                        {
                            equation += opButtons[i].getTextString().toAnsiString();
                        }
                        if (equation[equation.length()] == '=')
                        {
                            solveTime = true;
                            break;
                        }
                    }
                }
                std::cout << equation << std::endl;
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
    opButtons[0].setPosition(sf::Vector2f(420.f, 210.f));
    opButtons[0].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[0].setText("/", sf::Color::Black);
    opButtons[0].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[1].setPosition(sf::Vector2f(420.f, 315.f));
    opButtons[1].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[1].setText("*", sf::Color::Black);
    opButtons[1].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[2].setPosition(sf::Vector2f(420.f, 420.f));
    opButtons[2].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[2].setText("-", sf::Color::Black);
    opButtons[2].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[3].setPosition(sf::Vector2f(420.f, 525.f));
    opButtons[3].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[3].setText("+", sf::Color::Black);
    opButtons[3].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[4].setPosition(sf::Vector2f(315.f, 525.f));
    opButtons[4].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[4].setText("=", sf::Color::Black);
    opButtons[4].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(7 + j - (i * 3));
            numButtons[j + (3 * i)].setPosition(sf::Vector2f((105.f * j) + 105.f, 210.f + (105.f * i)));
            numButtons[j + (3 * i)].setSize(sf::Vector2f(100.f, 100.f));
            numButtons[j + (3 * i)].setText(str, sf::Color::Black);
            numButtons[j + (3 * i)].setMemberColor(sf::Color::White, sf::Color::Black);
        }
    }
    numButtons[9].setPosition(sf::Vector2f(210.f, 525.f));
    numButtons[9].setSize(sf::Vector2f(100.f, 100.f));
    numButtons[9].setText("0", sf::Color::Black);
    numButtons[9].setMemberColor(sf::Color::White, sf::Color::Black);
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
    }
    if (solveTime)
    {
        if (solveEquation(equation))
        {
            std::cout << "Solution: " << equation << std::endl;
        }
    }
}


bool solveEquation(std::string& equation)
{
    std::unordered_map<unsigned short int, char> operatorIndices;
    unsigned int opCount = 0;
    //Parse the equation to find the indexes of the operators
    for (int i = 0; i < equation.length(); i++)
    {
        if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')
            operatorIndices.emplace(i, equation[i]);
    }
    
    
}