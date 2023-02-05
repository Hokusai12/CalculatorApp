#pragma once
#include <string>
#include <cmath>

class Calculator
{
public:
	static bool checkEquation(std::string equation);
	static std::string solveEquation(std::string equation);
private:
	static double addNums(double a, double b) { return a + b; }
	static double subNums(double a, double b) { return a - b; }
	static double multNums(double a, double b) { return a * b; }
	static double divNums(double a, double b) { return a / b; }
	static double toPower(double a, double b) { return std::pow(a, b); }
};

