cmake_minimum_required(VERSION 3.16)

project(reprojection_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. 把重投影算法编译成一个库
add_library(reprojection_lib
    src/reprojection.cpp
)

# 让使用这个库的目标能找到 include/reprojection.h
target_include_directories(reprojection_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    
)

# 2. 主程序
add_executable(reprojection_demo
    src/main.cpp
)

target_link_libraries(reprojection_demo
    PRIVATE
        reprojection_lib
)

# 3. 测试程序
enable_testing()

add_executable(test_reprojection
    tests/test_reprojection.cpp
)

target_link_libraries(test_reprojection
    PRIVATE
        reprojection_lib
)

add_test(
    NAME reprojection_tests
    COMMAND test_reprojection
)