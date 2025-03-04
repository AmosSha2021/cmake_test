cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

# 全局配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置动态库输出路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib)
# 在根CMakeLists.txt中添加MinGW专用配置
if(MINGW)
    # 设置动态库生成路径
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
    
    # 添加MinGW兼容性编译选项
    add_compile_options(-static-libgcc -static-libstdc++)
endif()





# 添加日志模块（路径指向模块根目录）
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/LogModule)

add_subdirectory(${PROJECT_SOURCE_DIR}/modules/CoreModule)

# 主程序模块
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    LogModule  # 修正为子模块中定义的目标名称
    pthread
    CoreModule
)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreModule)

# 包含路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/LogModule/include  # 更新路径
)