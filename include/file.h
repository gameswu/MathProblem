// file.h
#pragma once

#include "problem.h"

#include <vector>

class File
{
public:
    File(std::vector<Problem *> problems, std::string fileName, int numProblems, bool needAnswer, int fileFormat);
    void generateFile();

private:
    std::vector<Problem *> problems;
    std::string fileName;
    int numProblems = 100;
    bool needAnswer = false;
    int fileFormat = 0; // 0: UnicodeMath, 1: LaTeX
};