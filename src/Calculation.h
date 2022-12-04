#pragma once
#include <vector>
#include <iostream>

namespace Calc
{
	double solveEquation(std::vector<char>& ops, std::vector<double>& nums);
	double addNums(double a, double b) { return a + b; }
	double subNums(double a, double b) { return a - b; }
	double multNums(double a, double b) { return a * b; }
	double divNums(double a, double b) { return a / b; }
}