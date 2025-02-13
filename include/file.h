// file.h
// 生成题目输出为txt文件
#pragma once

#include "problem.h"

#include <vector>

class File
{
public:
    File(std::vector<Problem *> problems, std::string fileName, int numProblems, bool needAnswer);
    void generateFile();

private:
    std::vector<Problem *> problems;
    std::string fileName;
    int numProblems = 100;
    bool needAnswer = false;
};