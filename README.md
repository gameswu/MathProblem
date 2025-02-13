# 琪露诺的完美算术教室

这是一个用于练习算术的小程序，可以生成一些算术题目并支持`.txt`和`.md`格式语法的输出。

## 从源码构建

### 环境要求
依赖于以下工具：
- `cmake`构建工具，版本不低于`3.10`
- `MinGW Makefiles`构建工具，版本不低于`4.2.1`
- `gcc`编译器，版本不低于`8.1.0`

支持的系统环境：
- Windows OS
- 支持OPenGL3

依赖于以下库：
- `Dear ImGui`图形库，版本`1.91.8`
- `glfw`窗口库，版本`3.4`

### 构建步骤
cmake正常配置即可，并使用`MinGW Makefiles`构建工具进行构建。

```shell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

## TODO

### 基础功能
- [x] 生成加减的算术题目
- [ ] 生成乘除运算的算术题目
- [ ] 生成小数、分数的算术题目
- [ ] 生成线性方程的算术题目

### 进阶功能
- [ ] 用户通过代数表达式自定义题目形式
- [ ] 生成可以简化运算的算术题目