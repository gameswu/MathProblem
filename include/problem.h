// problem.h
// 生成题目
#pragma once

#define LIMIT_TIMES 1000 // 生成题目的最大尝试次数

#include <string>

class Problem
{
public:
    Problem();
    virtual std::string getProblem() const = 0;
    virtual std::string getAnswer() const = 0;
    void setFormat(int format)
    {
        this->format = format;
    }

protected:
    std::string problem;
    std::string answer;
    int format = 0; // 0: UnicodeMath, 1: LaTeX

    virtual void generateProblem() = 0;
    bool isOverFlow = false;
};

/*
 * 加减法题目-整数
 */
class AddSubProblem : public Problem
{
public:
    AddSubProblem(int nums, int maxNum, int maxRes, int minRes, int format);

    std::string getProblem() const override
    {
        return problem;
    }

    std::string getAnswer() const override
    {
        return answer;
    }

    int nums;   // 题目中的数字个数
    int maxNum; // 题目中的数字最大值
    int maxRes; // 题目中的结果最大值
    int minRes; // 题目中的结果最小值

private:
    void generateProblem() override;
};

/*
 * 乘除法题目-整数带余数
 */
class MulDivProblem : public Problem
{
public:
    MulDivProblem(int flags, int firstDigits, int secondDigits, int format);

    std::string getProblem() const override
    {
        return problem;
    }

    std::string getAnswer() const override
    {
        return answer;
    }

    enum MulDivFlags
    {
        IS_DIV = 1, // 是否为除法题目
        HAS_REM = 2 // 是否带余数
    };

    int flags; // 题目类型标志
    // int nums;  // 题目中的数字个数 弃用，固定为2
    int firstDigits;  // 第一个数的位数
    int secondDigits; // 第二个数的位数

private:
    void generateProblem() override;
};