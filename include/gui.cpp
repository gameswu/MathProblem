#include "gui.h"
#include "file.h"
#include <vector>
#include <string>
#include <memory>
#include <windows.h>
#include <commdlg.h>

GUI::GUI()
    : numProblems(10), selectedProblemType(0), selectedFormat(0), needAnswer(false)
{
    problemTypes.push_back("无");
    problemTypes.push_back("加减法");
    // 可以添加更多题型

    outputFormats.push_back("UnicodeMath");
    outputFormats.push_back("LaTeX");
    // 可以添加更多输出格式

    strcpy(filePath, "output.txt"); // 默认文件路径
}

void GUI::render()
{
    // 设置窗口的初始大小和位置
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);

    ImGui::Begin("题目生成器", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoFocusOnAppearing);

    ImGui::InputInt("题目数量", &numProblems);

    std::vector<const char *> problemTypesCStr;
    for (const auto &type : problemTypes)
    {
        problemTypesCStr.push_back(type.c_str());
    }
    std::vector<const char *> outputFormatsCStr;
    for (const auto &format : outputFormats)
    {
        outputFormatsCStr.push_back(format.c_str());
    }
    if (ImGui::Combo("输出格式", &selectedFormat, outputFormatsCStr.data(), outputFormatsCStr.size()))
    {
        // 当输出格式发生变化时，设置对应的 Problem 类的 format 属性
        if (currentProblem != nullptr)
        {
            currentProblem->setFormat(selectedFormat);
        }
        else
        {
            currentProblem.reset();
        }
    }
    if (ImGui::Combo("题型", &selectedProblemType, problemTypesCStr.data(), problemTypesCStr.size()))
    {
        // 当题型发生变化时，实例化对应的 Problem 类
        if (selectedProblemType == 0)
        {
            currentProblem.reset();
        }
        else if (selectedProblemType == 1)
        {
            currentProblem = std::make_unique<AddSubProblem>(2, 100, 200, 0, selectedFormat);
        }
        else
        {
            currentProblem.reset();
        }
        // 可以添加更多题型的实例化逻辑
    }

    ImGui::SameLine(); // 将需要答案的控件放在题型右侧
    ImGui::Checkbox("需要答案", &needAnswer);
    ImGui::Separator();

    // 渲染对应题型的选项
    renderProblemOptions();
    ImGui::Separator();

    // 输入文件名
    ImGui::InputText("输出文件名", filePath, sizeof(filePath));
    ImGui::SameLine();
    if (ImGui::Button("选择文件"))
    {
        openFileDialog();
    }

    if (ImGui::Button("开始生成"))
    {
        generateProblems();
        ImGui::OpenPopup("完成提示");
    }

    if (ImGui::BeginPopupModal("完成提示", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("题目生成完成！");
        if (ImGui::Button("确定"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void GUI::renderProblemOptions()
{
    if (currentProblem)
    {
        // 根据当前题型的类型，渲染对应的选项
        if (auto addSubProblem = dynamic_cast<AddSubProblem *>(currentProblem.get()))
        {
            ImGui::InputInt("数字个数", &addSubProblem->nums);
            ImGui::InputInt("数字最大值", &addSubProblem->maxNum);
            ImGui::InputInt("结果最大值", &addSubProblem->maxRes);
            ImGui::InputInt("结果最小值", &addSubProblem->minRes);
        }
        // 可以添加更多题型的选项渲染逻辑
    }
}

void GUI::generateProblems()
{
    if (selectedProblemType == 0)
    {
        return;
    }
    std::vector<Problem *> problems;
    for (int i = 0; i < numProblems; ++i)
    {
        if (selectedProblemType == 1)
        {
            problems.push_back(new AddSubProblem(dynamic_cast<AddSubProblem *>(currentProblem.get())->nums,
                                                 dynamic_cast<AddSubProblem *>(currentProblem.get())->maxNum,
                                                 dynamic_cast<AddSubProblem *>(currentProblem.get())->maxRes,
                                                 dynamic_cast<AddSubProblem *>(currentProblem.get())->minRes,
                                                 selectedFormat));
        }
        // 可以添加更多题型的生成逻辑
    }

    File file(problems, filePath, numProblems, needAnswer);
    file.generateFile();

    // 清理内存
    for (auto problem : problems)
    {
        delete problem;
    }
}

void GUI::openFileDialog()
{
    OPENFILENAME ofn;
    char szFile[256] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text Files\0*.txt\0Markdown Files\0*.md\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        strcpy(filePath, ofn.lpstrFile);
    }
}