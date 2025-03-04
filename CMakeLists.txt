cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

# 全局配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置动态库输出路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# 添加日志模块（路径指向模块根目录）
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/LogModule)

# 主程序模块
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    LogModule  # 使用新模块名称
    pthread
)

# 包含路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/LogModule/include  # 更新路径
)