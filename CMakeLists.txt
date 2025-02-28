cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MathProblem)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include
    3rdparty/imgui
    3rdparty/imgui/backends
    3rdparty/glfw/include
    3rdparty/json/include
    updater
)

# 添加imgui源文件
set(IMGUI_SRC
    3rdparty/imgui/imgui.cpp
    3rdparty/imgui/imgui_draw.cpp
    3rdparty/imgui/imgui_tables.cpp
    3rdparty/imgui/imgui_widgets.cpp
    3rdparty/imgui/backends/imgui_impl_glfw.cpp
    3rdparty/imgui/backends/imgui_impl_opengl3.cpp
)

# 添加json源文件
set(JSON_SRC
    3rdparty/json/src/lib_json/json_reader.cpp
    3rdparty/json/src/lib_json/json_value.cpp
    3rdparty/json/src/lib_json/json_writer.cpp
)

# 添加源文件
add_executable(MathProblem WIN32
    main.cpp
    resource.rc
    include/problem.cpp
    include/file.cpp
    include/gui.cpp
    include/log.cpp
    ${IMGUI_SRC}
)

# 添加Updater GUI的构建配置
add_executable(Updater_GUI WIN32
    updater_gui.cpp
    updater/update.cpp
    ${IMGUI_SRC}
    ${JSON_SRC}
)

# 链接库
find_package(OpenGL REQUIRED)

target_link_directories(MathProblem PRIVATE 3rdparty/glfw/lib-mingw-w64)
target_link_libraries(MathProblem OpenGL::GL glfw3)
target_link_directories(Updater_GUI PRIVATE 3rdparty/glfw/lib-mingw-w64)
target_link_libraries(Updater_GUI OpenGL::GL glfw3)

# 设置构建类型为Release
set(CMAKE_BUILD_TYPE Release)

# 设置为debug模式
# set(CMAKE_BUILD_TYPE Debug)

# 打开 Release 模式的静态链接选项
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static -static-libgcc -static-libstdc++ -Os")

# 打开 Debug 模式的静态链接选项
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -static -static-libgcc -static-libstdc++")

# 强制对 libstdc++、libgcc使用静态链接
set(BUILD_SHARED_LIBS OFF)

# 保留资源文件夹assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})