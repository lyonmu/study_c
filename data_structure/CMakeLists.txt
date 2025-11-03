# CMake 配置文件
# 用于构建数据结构学习项目的构建系统配置

# 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.25)

# 定义项目名称和使用的编程语言
# 项目名称: data_structure
# 语言: C
project(data_structure C)

# 指定 C 标准版本
# 使用 C11 标准
set(CMAKE_C_STANDARD 11)

# 设置可执行文件的输出目录
# 将编译生成的可执行文件放到 build/bin 目录中
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# 添加可执行文件目标
# 可执行文件名: data_structure
# 源文件: main.c
add_executable(data_structure main.c)
