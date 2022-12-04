#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Button.h"
#include "TextArea.h"

void appInit();
void appDraw(sf::RenderWindow& window);
void appUpdate(sf::RenderWindow& window);

bool checkEquation();
double solveEquation(std::string &equation);
double addNums(double a, double b) { return a + b; }
double subNums(double a, double b) { return a - b; }
double multNums(double a, double b) { return a * b; }
double divNums(double a, double b) { return a / b; }

sf::Font appFont;
GUI::Button numButtons[10];
GUI::Button opButtons[10];
GUI::Button clrButton;
GUI::TextArea equationDisplay;



int main()
{

    std::string equation = "";

    sf::RenderWindow window(sf::VideoMode(425, 640), "Calculator");

    appInit();



    /*      APP LOOP
    1.Draw Window
    2.Update App States
    3.Check for Button states
        3a. If number button is active, add button's text to string
        3b. If operator button is active, add button's text to string
        3c. Clear the TextArea display when the 'clr' button is pressed
        3(edge cases):
            Operator Button (not '(') pressed without a number in equation (i.e. '+ 2')
            Num button '0' pressed after a dividing operator '/'
    4.Wait for '=' operator button to be pressed
    5.Solve the Equation
    6.Return solution to the TextArea Display
    7.Allow the user to continue working on the solution

    */
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
                    //Check to see what button is pressed
                    for (int i = 0; i < 10; i++)
                    {
                        if (numButtons[i].isActive())
                        {
                            equation += numButtons[i].getTextString().toAnsiString();
                            equationDisplay.setText(equation);
                        }
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        if (opButtons[i].isActive())
                        {
                            //Check if the last character of the equation is an operator
                            if ((equation[equation.size() - 1] == '*'
                                || equation[equation.size() - 1] == '/'
                                || equation[equation.size() - 1] == '-'
                                || equation[equation.size() - 1] == '+'
                                || equation[equation.size() - 1] == '^')
                                && opButtons[i].getTextString().toAnsiString() != "(")
                            {
                                equation[equation.size() - 1] = opButtons[i].getTextString().toAnsiString()[0];
                            }
                            else if (opButtons[i].getTextString().toAnsiString() == "(" &&
                                (equation[equation.size() - 1] != '*'
                                    && equation[equation.size() - 1] != '/'
                                    && equation[equation.size() - 1] != '-'
                                    && equation[equation.size() - 1] != '+'
                                    && equation[equation.size() - 1] != '^'))
                            {
                                equation += "*(";
                            }
                            else if (equation.substr(equation.size() - 2, 2) == "*(")
                            {
                                equation.erase(equation.size() - 2, 2);
                                equation += opButtons[i].getTextString().toAnsiString();
                            }
                            else if (opButtons[i].getTextString().toAnsiString() == "=")
                            {
                                double solution = 0.0;
                                if(checkEquation())
                                    solution = solveEquation(equation);
                                equationDisplay.setText(std::to_string(solution));
                                break;
                            }
                            else
                            {
                                equation += opButtons[i].getTextString().toAnsiString();
                            }
                            equationDisplay.setText(equation);
                        }
                    }
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
    if (!appFont.loadFromFile("assets/fonts/ArialTh.ttf"))
        std::cerr << "Couldn't load font file!" << std::endl;


    equationDisplay = new GUI::TextArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(425.f, 110.f), "", appFont);

    //Create all of the operator buttons
    opButtons[0] = new GUI::Button(sf::Vector2f(110.f, 115.f), sf::Vector2f(100.f, 100.f), "(", appFont);
    opButtons[1] = new GUI::Button(sf::Vector2f(215.f, 115.f), sf::Vector2f(100.f, 100.f), ")", appFont);
    opButtons[2] = new GUI::Button(sf::Vector2f(320.f, 115.f), sf::Vector2f(100.f, 100.f), "^", appFont);
    opButtons[3] = new GUI::Button(sf::Vector2f(320.f, 220.f), sf::Vector2f(100.f, 100.f), "/", appFont);
    opButtons[4] = new GUI::Button(sf::Vector2f(320.f, 325.f), sf::Vector2f(100.f, 100.f), "*", appFont);
    opButtons[5] = new GUI::Button(sf::Vector2f(320.f, 430.f), sf::Vector2f(100.f, 100.f), "+", appFont);
    opButtons[6] = new GUI::Button(sf::Vector2f(320.f, 535.f), sf::Vector2f(100.f, 100.f), "-", appFont);
    opButtons[8] = new GUI::Button(sf::Vector2f(215.f, 535.f), sf::Vector2f(100.f, 100.f), "=", appFont);
    opButtons[9] = new GUI::Button(sf::Vector2f(5.f, 535.f), sf::Vector2f(100.f, 100.f), ".", appFont);
    for (int i = 0; i < 10; i++)
    {
        opButtons[i].setBoxColor(sf::Color::Color(180, 180, 180));
    }

    //Create all of the number buttons
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string str = std::to_string(7 + j - (i * 3));
            numButtons[j + (3 * i)] = new GUI::Button(
                sf::Vector2f((105.f * j) + 5.f, 220.f + (105.f * i)),
                sf::Vector2f(100.f, 100.f),
                str,
                appFont);
        }
    }
    numButtons[9] = new GUI::Button(sf::Vector2f(110.f, 535.f), sf::Vector2f(100.f, 100.f), "0", appFont);

    //Clear Button
    clrButton = new GUI::Button(sf::Vector2f(5.f, 115.f), sf::Vector2f(100.f, 100.f), "CLR", appFont);
    clrButton.setBoxColor(sf::Color::Color(180, 180, 180));
}

void appDraw(sf::RenderWindow &window)
{
    for (int i = 0; i < 10; i++)
    {
        numButtons[i].draw(window);
    }
    for (int i = 0; i < 10; i++)
    {
        opButtons[i].draw(window);
    }
    equationDisplay.draw(window);
    clrButton.draw(window);
}

void appUpdate(sf::RenderWindow &window)
{
    for (int i = 0; i < 10; i++)
    {
        numButtons[i].update(window);
    }
    for (int i = 0; i < 10; i++)
    {
        opButtons[i].update(window);
    }
    clrButton.update(window);
}

double solveEquation(std::string &equation)
{
    double solution = 0.0;

    if (nums.size() == 1)
    {
        return nums.at(0);
    }

    //Perform one set of operations on the equation
    if (ops.size() > 0)
    {
        if (vecContains<char>(ops, '(') && vecContains<char>(ops, ')'))
        {
            std::vector<double> parNums;
            std::vector<char> parOps;
            for (unsigned int i = 0; i < ops.size(); i++)
            {
                if (ops.at(i) == '(')
                {
                    for (unsigned int j = 0; ops.at(j) == ')' || j < ops.size(); j++)
                    {
                        parOps.emplace_back(ops.at(j));
                        parNums.emplace_back(nums.at(j));
                    }
                }
            }
        }
        else if (vecContains<char>(ops, '^'))
        {

        }
        else if (vecContains<char>(ops, '*') || vecContains<char>(ops, '/'))
        {
            for (unsigned int i = 0; i < ops.size(); i++)
            {
                if (ops.at(i) == '*')
                {
                    const double product = multNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter + 2);
                    nums.emplace(numsIter, product);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                if (ops.at(i) == '/')
                {
                    const double quotient = divNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter + 2);
                    nums.insert(numsIter, quotient);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                opsIter++;
                numsIter++;
            }
        }
        else if (vecContains<char>(ops, '+') || vecContains<char>(ops, '-'))
        {
            for (unsigned int i = 0; i < ops.size(); i++)
            {
                if (ops.at(i) == '+')
                {
                    const double sum = addNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter + 2);
                    nums.insert(numsIter, sum);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                if (ops.at(i) == '-')
                {
                    const double difference = subNums((double)nums.at(i), (double)nums.at(i + 1));
                    numsIter = nums.erase(numsIter, numsIter + 2);
                    nums.insert(numsIter, difference);
                    ops.erase(opsIter, opsIter + 1);
                    break;
                }
                opsIter++;
                numsIter++;
            }
        }
    }
    if (nums.size() > 1)
    {
        solution = solveEquation(ops, nums);
    }
    else
    {
        solution = nums.at(0);
    }
    return solution;
}

