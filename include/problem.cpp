#include "problem.h"
#include "log.h"
#include "utils.h"
#include <random>
#include <cmath>

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

/* 生成加减法题目-整数
 *
 * 在UnicodeMath和LaTeX两种格式下输出格式分别为：
 * UnicodeMath: 1 + 2 - 3 =
 * LaTeX: 1+2-3= \\
 */
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
    bool isOverFlow = false;
    int times = 0;
    do
    {
        res = 0;
        prob = "";
        ans = "";
        isOverFlow = false;
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
                    if (res > INT_MAX - num)
                    {
                        isOverFlow = true;
                        break;
                    }
                    res += num;
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
                    if (res < INT_MIN + num)
                    {
                        isOverFlow = true;
                        break;
                    }
                    res -= num;
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
        times++;
    } while (res < minRes || res > maxRes || isOverFlow || times > LIMIT_TIMES);

    if (isOverFlow)
    {
        Logger::getInstance().log("In Problem " + prob + ": Overflow in numerical calculations", WARNING);
    }
    else if (times > LIMIT_TIMES)
    {
        Logger::getInstance().log("In Problem " + prob + ": Failed to generate in LIMIT_TIMES", ERROR);
    }

    ans = std::to_string(res);
    problem = prob;
    answer = ans;
}

MulDivProblem::MulDivProblem(int flags, int firstDigits, int secondDigits, int format)
{
    this->flags = flags;
    this->firstDigits = firstDigits;
    this->secondDigits = secondDigits;
    this->format = format;
    generateProblem();
}

/* 生成乘除法题目-整数带余数
 *
 * 在UnicodeMath和LaTeX两种格式下输出格式分别为：
 * UnicodeMath: 13 ÷ 3 = 4 ... 1
 * LaTeX: 13 \div 3 = 4 \cdots 1
 */
void MulDivProblem::generateProblem()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> numDist1(std::pow(10, firstDigits - 1), std::pow(10, firstDigits) - 1);
    std::uniform_int_distribution<> numDist2(std::pow(10, secondDigits - 1), std::pow(10, secondDigits) - 1);

    std::string prob = "";
    std::string ans = "";
    int num1 = numDist1(gen);
    int num2 = numDist2(gen);
    int res = 0;
    int rem = 0;
    bool isOverFlow = false;
    int times = 0;

    do
    {
        if (!(flags & IS_DIV))
        {
            res = num1 * num2;
            if (res > INT_MAX)
            {
                isOverFlow = true;
            }
            if (format == 0)
            {
                prob = std::to_string(num1) + " × " + std::to_string(num2) + " = ";
            }
            else
            {
                prob = std::to_string(num1) + " \\times " + std::to_string(num2) + "=";
            }
            ans = std::to_string(res);
        }
        else
        {
            std::uniform_int_distribution<> remDist(1, num2 - 1);
            std::uniform_int_distribution<> resDist(std::pow(10, firstDigits - 1) / num2, (std::pow(10, firstDigits) - 1) / num2);
            res = resDist(gen);
            rem = remDist(gen);
            if (!(flags & HAS_REM))
            {
                rem = 0;
            }
            if (res > INT_MAX / num2 || res * num2 > INT_MAX - rem)
            {
                isOverFlow = true;
            }
            num1 = res * num2 + rem;
            if (format == 0)
            {
                prob = std::to_string(num1) + " ÷ " + std::to_string(num2) + " = ";
                if (rem == 0)
                {
                    ans = std::to_string(res);
                }
                else
                {
                    ans = std::to_string(res) + " ... " + std::to_string(rem);
                }
            }
            else
            {
                prob = std::to_string(num1) + " \\div " + std::to_string(num2) + "=";
                if (rem == 0)
                {
                    ans = std::to_string(res);
                }
                else
                {
                    ans = std::to_string(res) + " \\cdots " + std::to_string(rem);
                }
            }
        }
        times++;
    } while (isOverFlow || times > LIMIT_TIMES || num2 == 0 || num1 < std::pow(10, firstDigits - 1) || num1 >= std::pow(10, firstDigits));

    if (isOverFlow)
    {
        Logger::getInstance().log("In Problem " + prob + ": Overflow in numerical calculations", WARNING);
    }
    else if (times > LIMIT_TIMES)
    {
        Logger::getInstance().log("In Problem " + prob + ": Failed to generate in LIMIT_TIMES", ERROR);
    }

    problem = prob;
    answer = ans;
}