#include "problem.h"
#include <random>

Problem::Problem()
{
    problem = "";
    answer = "";
}

AddSubProblem::AddSubProblem(int nums, int maxNum, int maxRes, int minRes, int format)
{
    this->nums = nums;
    this->maxNum = maxNum;
    this->maxRes = maxRes;
    this->minRes = minRes;
    this->format = format;
    generateProblem();
}

void AddSubProblem::generateProblem()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> numDist(1, maxNum);
    std::uniform_int_distribution<> opDist(0, 1);

    std::string prob = "";
    std::string ans = "";
    int res = 0;
    int num = 0;
    int op = 0;
    do
    {
        res = 0;
        prob = "";
        ans = "";
        for (int i = 0; i < nums; i++)
        {
            num = numDist(gen);
            op = opDist(gen);
            if (i == 0)
            {
                prob += std::to_string(num);
                res = num;
            }
            else
            {
                if (op == 0)
                {
                    if (format == 0)
                    {
                        prob += " + " + std::to_string(num);
                    }
                    else
                    {
                        prob += "+" + std::to_string(num);
                    }
                }
                else
                {
                    if (format == 0)
                    {
                        prob += " - " + std::to_string(num);
                    }
                    else
                    {
                        prob += "-" + std::to_string(num);
                    }
                }
            }
        }
        if (format == 0)
        {
            prob += " = ";
        }
        else
        {
            prob += "=";
        }
    } while (res < minRes || res > maxRes);
    ans = std::to_string(res);
    problem = prob;
    answer = ans;
}