#include "Calculator.h"
#include <iostream>

bool Calculator::checkEquation(std::string equation)
{
    return true;
}

std::string Calculator::solveEquation(std::string equation)
{
    std::cout << "Equation before: " << equation << std::endl;
    //Follows PEMDAS
    /*
        1. Locate the innermost Parentheses phrase
        2. Solve and return to original equation
        3. Loop until Parentheses are solved
        4. Solve the Exponents LtoR
        5. Solve the Multiplication and Division phrases LtoR
        6. Solve the Addition and Subtraction phrases LtoR
    */
    //Locates the first "(" and the last ")" and recursively solve any parentheses in between
    std::cout << "Finding Parentheses..." << std::endl;
    unsigned int par_end_index = equation.find_first_of(")");
    unsigned int par_start_index = 0, subequation_start = 0, subequation_end = 0;
    while (true)
    {
        if (par_end_index != std::string::npos)
        {
            std::cout << "Parentheses found..." << std::endl;

            for (int i = par_end_index; i >= 0; i--)
            {
                if (equation.at(i) == '(')
                {
                    par_start_index = i;
                    break;
                }
            }

            std::string par_equation = equation.substr(par_start_index + 1, par_end_index - (par_start_index + 1));
            std::cout << "Parentheses equation before : " << par_equation << std::endl;
            par_equation = solveEquation(par_equation);
            equation.replace(par_start_index, (par_end_index + 1) - par_start_index, par_equation);
            std::cout << "Parentheses equation after: " << equation << std::endl;
        }
        else
        {
            break;
        }
        par_end_index = equation.find_first_of(")");
    }
    std::cout << "Finding exponents..." << std::endl;
    //Locate the first "^" and just math all of them lol
    par_start_index = equation.find_first_of("^");
    while (par_start_index != std::string::npos)
    {
        std::cout << "Equation before: " << equation << std::endl;
        par_end_index = par_start_index;
        double a, b;
        std::string num = "";

        for (int i = par_start_index - 1; i >= 0; i--)
        {
            if (equation.at(i) == '+' ||
                equation.at(i) == '-' ||
                equation.at(i) == '*' ||
                equation.at(i) == '/' ||
                equation.at(i) == '^')
            {
                subequation_start = i + 1;
                num = equation.substr(subequation_start, par_end_index - i);
                i = -1;
            }
            else if (i == 0)
            {
                subequation_start = 0;
                num = equation.substr(i, par_end_index - i);
            }

        }
        std::cout << "First number: " << num << std::endl;

        a = std::atof(num.c_str());
        num = "";
        par_start_index = par_end_index;
        for (int i = par_end_index + 1; i < equation.size(); i++)
        {
            if (equation.at(i) != '+' &&
                equation.at(i) != '-' &&
                equation.at(i) != '*' &&
                equation.at(i) != '/' &&
                equation.at(i) != '^')
            {
                num += equation.at(i);
                subequation_end = i + 1;
            }
            else
            {
                subequation_end = i;
                par_end_index = i - 1;
                break;
            }
        }
        std::cout << "Second number: " << num << std::endl;

        b = std::atof(num.c_str());

        double product = toPower(a, b);
        std::cout << "Exponent Answer: " << std::to_string(product) << std::endl;

        equation.erase(subequation_start, subequation_end - subequation_start);
        equation.insert(subequation_start, std::to_string(product));

        std::cout << "Equation after: " << equation << std::endl;
        par_start_index = equation.find_first_of("^");
    }

    std::cout << "Finding products and quotients..." << std::endl;

    par_start_index = equation.find_first_of("*/");
    while (par_start_index != std::string::npos)
    {
        std::cout << "Equation before: " << equation << std::endl;
        par_end_index = par_start_index;
        char activeOp = equation.at(par_end_index);
        double a, b;
        std::string num = "";
        for (int i = par_start_index - 1; i >= 0; i--)
        {
            if (equation.at(i) == '+' ||
                equation.at(i) == '-' ||
                equation.at(i) == '*' ||
                equation.at(i) == '/' ||
                equation.at(i) == '^')
            {
                subequation_start = i + 1;
                num = equation.substr(subequation_start, par_end_index - subequation_start);
                break;
            }
            else if (i == 0)
            {
                subequation_start = 0;
                num = equation.substr(i, par_end_index - i);
            }
            
        }
        std::cout << "First number: " << num << std::endl;

        a = std::atof(num.c_str());
        num = "";
        for (int i = par_end_index + 1; i < equation.size(); i++)
        {
            if (equation.at(i) != '+' &&
                equation.at(i) != '-' &&
                equation.at(i) != '*' &&
                equation.at(i) != '/' &&
                equation.at(i) != '^')
            {
                num += equation.at(i);
                subequation_end = i + 1;
            }
            else
            {
                subequation_end = i;
                par_end_index = i;
                break;
            }

        }
        std::cout << "Second number: " << num << std::endl;

        b = std::atof(num.c_str());

        double product = (activeOp == '*') ? multNums(a, b) : divNums(a, b);
        std::cout << "Answer: " << product << std::endl;
        equation.erase(subequation_start, subequation_end - subequation_start);
        equation.insert(subequation_start, std::to_string(product));
        std::cout << "Equation after: " << equation << std::endl;

        par_start_index = equation.find_first_of("*/");

    }

    std::cout << "Finding addition or subtraction instances..." << std::endl;

    par_start_index = equation.find_first_of("+-");
    while (par_start_index != std::string::npos)
    {
        std::cout << "Equation before: " << equation << std::endl;
        par_end_index = par_start_index;
        char activeOp = equation.at(par_end_index);
        double a, b;
        std::string num = "";
        for (int i = par_start_index - 1; i >= 0; i--)
        {
            if (equation.at(i) == '+' ||
                equation.at(i) == '-' ||
                equation.at(i) == '*' ||
                equation.at(i) == '/' ||
                equation.at(i) == '^')
            {
                subequation_start = i + 1;
                num = equation.substr(i + 1, par_start_index - i);
            }
            else if (i == 0)
            {
                subequation_start = 0;
                num = equation.substr(i, par_start_index);
            }
        }
        std::cout << "First number: " << num << std::endl;
        a = std::atof(num.c_str());
        num = "";
        for (int i = par_end_index + 1; i < equation.size(); i++)
        {
            if (equation.at(i) != '+' &&
                equation.at(i) != '-' &&
                equation.at(i) != '*' &&
                equation.at(i) != '/' &&
                equation.at(i) != '^')
            {
                num += equation.at(i);
                subequation_end = i + 1;
            }
            else
            {
                subequation_end = i;
                par_end_index = i;
                break;
            }
        }
        std::cout << "Second number: " << num << std::endl;
        b = std::atof(num.c_str());

        double product = (activeOp == '+') ? addNums(a, b) : subNums(a, b);
        std::cout << "Answer: " << product << std::endl;
        equation.erase(subequation_start, subequation_end - subequation_start);
        equation.insert(subequation_start, std::to_string(product));
        std::cout << "Equation after: " << equation << std::endl;

        par_start_index = equation.find_first_of("+-");
    }

    std::cout << "Solution: " << equation << std::endl;

    return equation;
}