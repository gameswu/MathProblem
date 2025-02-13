// problem.h
// 生成题目
#pragma once

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
};

/*
 * 加减法题目
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