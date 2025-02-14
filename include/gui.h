// gui.h
#pragma once

#include "imgui.h"
#include "problem.h"
#include <vector>
#include <string>
#include <memory>

class GUI
{
public:
    GUI();
    void render();

private:
    int numProblems;
    std::vector<std::string> problemTypes;
    std::vector<std::string> outputFormats;
    int selectedProblemType;
    int selectedFormat;
    bool needAnswer;
    char filePath[256]; // 用于存储文件路径

    std::unique_ptr<Problem> currentProblem; // 使用智能指针管理 Problem 对象

    void generateProblems();
    void renderProblemOptions(); // 根据题型渲染对应的选项
    void openFileDialog();       // 打开文件对话框选择文件路径
};