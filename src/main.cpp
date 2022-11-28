#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "Button.h"
#include "TextArea.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate(sf::RenderWindow &window);
double solveEquation(std::vector<char>& ops, std::vector<double>& nums, const char* activeOp);
double addNums(double a, double b) { return a + b; }
double subNums(double a, double b) { return a - b; }
double multNums(double a, double b) { return a * b; }
double divNums(double a, double b) { return a / b; }


GUI::Button numButtons[10];
GUI::Button opButtons[5];
GUI::Button clrButton(sf::Vector2f(70.f, 465.f), sf::Vector2f(100.f, 100.f), "CLR");
GUI::TextArea equationDisplay(sf::Vector2f(5.f, 10.f), sf::Vector2f(490.f, 105.f), "");

bool solveTime = false;
bool isSolved = false;
std::string number = "";
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
                            if (isSolved)
                            {
                                equationDisplay.clearText();
                                isSolved = false;
                            }
                            number += numButtons[i].getTextString().toAnsiString();
                            equationDisplay.concatText(numButtons[i].getTextString().toAnsiString());
                        }
                    }
                    for (int i = 0; i < 5; i++)
                    {
                        if (opButtons[i].isActive())
                        {
                            operators.emplace_back(opButtons[i].getTextString().toAnsiString()[0]);
                            numbers.emplace_back((double)atoi(number.c_str()));
                            equationDisplay.concatText(opButtons[i].getTextString().toAnsiString()[0]);
                            number = "";
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
                        equationDisplay.setText("");
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
    opButtons[0].setPosition(sf::Vector2f(385.f, 150.f));
    opButtons[0].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[0].setText("/", sf::Color::Black);
    opButtons[0].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[1].setPosition(sf::Vector2f(385.f, 255.f));
    opButtons[1].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[1].setText("*", sf::Color::Black);
    opButtons[1].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[2].setPosition(sf::Vector2f(385.f, 360.f));
    opButtons[2].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[2].setText("-", sf::Color::Black);
    opButtons[2].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[3].setPosition(sf::Vector2f(385.f, 465.f));
    opButtons[3].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[3].setText("+", sf::Color::Black);
    opButtons[3].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);
    opButtons[4].setPosition(sf::Vector2f(280.f, 465.f));
    opButtons[4].setSize(sf::Vector2f(100.f, 100.f));
    opButtons[4].setText("=", sf::Color::Black);
    opButtons[4].setMemberColor(sf::Color::Color(180, 180, 180), sf::Color::Black);


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(7 + j - (i * 3));
            numButtons[j + (3 * i)].setPosition(sf::Vector2f((105.f * j) + 70.f, 150.f + (105.f * i)));
            numButtons[j + (3 * i)].setSize(sf::Vector2f(100.f, 100.f));
            numButtons[j + (3 * i)].setText(str, sf::Color::Black);
            numButtons[j + (3 * i)].setMemberColor(sf::Color::White, sf::Color::Black);
        }
    }
    numButtons[9].setPosition(sf::Vector2f(175.f, 465.f));
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
    if (solveTime)
    {
        double solution = solveEquation(operators, numbers, "*/");
        if (solution - std::trunc(solution) > 0)
        {
            equationDisplay.setText(std::to_string(solution));
        }
        else
        {
            equationDisplay.setText(std::to_string((int)solution));
        }
        numbers.clear();
        operators.clear();
        solveTime = false;
        isSolved = true;
    }
}

double solveEquation(std::vector<char> &ops, std::vector<double> &nums, const char* activeOp)
{
    std::vector<double>::iterator numsIter = nums.begin();
    std::vector<char>::iterator opsIter = ops.begin();
    const char* newActiveOp = "";
    double solution = 0.0;

    if (nums.size() == 1)
    {
        return nums.at(0);
    }

    //Perform one set of operations on the equation
    if (ops.size() > 0)
    {
        if (activeOp == "*/")
        {
            for (unsigned int i = 0; i < ops.size(); i++)
            {
                if (ops.at(i) == '*')
                {
                    const double product = multNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter+2);
                    nums.emplace(numsIter, product);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                if (ops.at(i) == '/')
                {
                    const double quotient = divNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter+2);
                    nums.insert(numsIter, quotient);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                opsIter++;
                numsIter++;
            }
            //Check for activeOps in the operations vector
            for (unsigned int j = 0; j < ops.size(); j++)
            {
                if (ops.at(j) == '*' || ops.at(j) == '/')
                {
                    newActiveOp = activeOp;
                    break;
                }
                else
                    newActiveOp = "+-";
            }
        }
        if (activeOp == "+-")
        {
            for (unsigned int i = 0; i < ops.size(); i++)
            {
                if (ops.at(i) == '+')
                {
                    const double sum = addNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter+2);
                    nums.insert(numsIter, sum);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                if (ops.at(i) == '-')
                {
                    const double difference = subNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter+2);
                    nums.insert(numsIter, difference);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                opsIter++;
                numsIter++;
            }
            //Check for activeOps in the operations vector
            for (unsigned int j = 0; j < ops.size(); j++)
            {
                if (ops.at(j) == '+' || ops.at(j) == '-')
                    newActiveOp = activeOp;
            }
        }
    }
    if (nums.size() > 1)
    {
        solution = solveEquation(ops, nums, newActiveOp);
    }
    else
    {
        solution = nums.at(0);
    }
    return solution;
}