#define GLFW_EXPOSE_NATIVE_WIN32

#include "gui.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "resource.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <windows.h>

void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int, char **)
{
    // 设置GLFW错误回调
    glfwSetErrorCallback(glfw_error_callback);

    // 初始化GLFW
    if (!glfwInit())
        return -1;

    // 设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(1600, 900, "琪露诺的完美算术教室", nullptr, nullptr);
    if (window == nullptr)
        return -1;

    glfwMakeContextCurrent(window);
    glfwFocusWindow(window);
    glfwSwapInterval(1); // Enable vsync

    // 设置窗口图标
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON));
    if (hIcon)
    {
        HWND hwnd = glfwGetWin32Window(window);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }

    // 初始化imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // 设置imgui样式
    ImGui::StyleColorsDark();

    // 加载中文字体
    io.Fonts->AddFontFromFileTTF("assets/fonts/msyh.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

    // 初始化imgui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 创建GUI对象
    GUI gui;

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 启动新帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 设置窗口大小和位置与Win窗口一致
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui::SetNextWindowSize(ImVec2(display_w, display_h));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        // 渲染GUI
        ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        gui.render();
        ImGui::End();

        // 渲染
        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 交换缓冲区
        glfwSwapBuffers(window);
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
