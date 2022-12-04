#include "Calculation.h"

namespace Calc
{
    template <typename T>
    bool vecContains(std::vector<T> vec, T element)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec.at(i) == element)
                return true;
        }
        return false;
    }

    double solveEquation(std::vector<char>& ops, std::vector<double>& nums)
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

}