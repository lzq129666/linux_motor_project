# 1. 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.16)

# 2. 声明项目名称和使用的语言
project(LinuxMotorProject LANGUAGES CXX)

# 3. 要求使用 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. 告诉 CMake 去哪里找头文件（相当于 -Iinclude）
include_directories(${PROJECT_SOURCE_DIR}/include)

# 5. 收集你的源文件
# 注意：以后你每新加一个 .cpp，就必须把它的路径加到这里！
set(MOTOR_SOURCES
    src/motor.cpp
    src/motor_simulator.cpp
    src/pid_controller.cpp
)

# 6. 定义最终生成的可执行程序
add_executable(motor_app
    apps/motor_sim_main.cpp 
    ${MOTOR_SOURCES}
)

# 7. 开启编译警告（相当于 -Wall -Wextra -Wpedantic）
target_compile_options(motor_app PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)