# 使用相对路径定位源文件
add_library(LogModule SHARED  # 修改为SHARED
    src/Logger.cpp
)

# 保持头文件包含
target_include_directories(LogModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 增加符号可见性控制（可选）
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(LogModule PRIVATE -fvisibility=hidden)
endif()

# 设置动态库版本
set_target_properties(LogModule PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    SOVERSION 1
    VERSION 1.0.0
    # Windows系统需要导出符号
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# 链接线程库
target_link_libraries(LogModule PRIVATE 
    pthread
)

# 添加模块导出定义
target_compile_definitions(LogModule PRIVATE
    LOG_MODULE_EXPORTS
)
