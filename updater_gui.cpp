#include "updater/update.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <windows.h>

std::atomic<bool> isUpdating(false);
std::atomic<float> progress(0.0f);
std::string updateStatus = "Checking for updates...";
char proxy[256] = "127.0.0.1:7890";
int retries = 1;

void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void checkForUpdates()
{
    std::string repo = "gameswu/MathProblem";
    std::string latestVersion;

    if (Updater::checkForUpdates(repo, latestVersion, proxy, retries))
    {
        updateStatus = "Latest version: " + latestVersion;
        std::string downloadUrl = "https://github.com/" + repo + "/releases/download/" + latestVersion + "/" + latestVersion + ".zip";
        std::string outputPath = latestVersion + ".zip";

        isUpdating = true;
        std::thread downloadThread([downloadUrl, outputPath]()
                                   {
            if (Updater::downloadUpdate(downloadUrl, outputPath, proxy, retries))
            {
                updateStatus = "Update downloaded successfully to " + outputPath;
            }
            else
            {
                updateStatus = "Failed to download update.";
            }
            isUpdating = false; });
        downloadThread.detach();
    }
    else
    {
        updateStatus = "Failed to check for updates.";
    }
}

int main(int, char **)
{
    // 隐藏命令行窗口
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

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
    GLFWwindow *window = glfwCreateWindow(800, 600, "Updater", nullptr, nullptr);
    if (window == nullptr)
        return -1;

    glfwMakeContextCurrent(window);
    glfwFocusWindow(window);
    glfwSwapInterval(1); // Enable vsync

    // 初始化imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // 设置imgui样式
    ImGui::StyleColorsDark();

    // 初始化imgui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 检查更新
    std::thread checkThread(checkForUpdates);
    checkThread.detach();

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 启动新帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 渲染GUI
        ImGui::Begin("Updater");

        ImGui::Text("%s", updateStatus.c_str());

        if (isUpdating)
        {
            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        }

        ImGui::InputText("proxy", proxy, sizeof(proxy));

        if (ImGui::Button("Retry"))
        {
            std::thread retryThread(checkForUpdates);
            retryThread.detach();
        }

        ImGui::End();

        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
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
