# 使用相对路径定位源文件
add_library(LogModule SHARED
    src/Logger.cpp
)

target_include_directories(LogModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MINGW)
    # MinGW需要显式链接标准库
    target_link_libraries(LogModule PRIVATE 
        pthread
        stdc++fs  # 支持filesystem库
    )
else()
    target_link_libraries(LogModule PRIVATE 
        pthread
    )
endif()

# 设置动态库版本
set_target_properties(LogModule PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    SOVERSION 1
    VERSION 1.0.0
    # Windows系统需要导出符号
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# 添加模块导出定义
target_compile_definitions(LogModule PRIVATE
    LOG_MODULE_EXPORTS
)

# 在模块级CMakeLists中配置头文件结构
target_include_directories(LogModule PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MINGW)
    # 添加静态链接选项
    target_link_options(LogModule PRIVATE
        -static-libstdc++
        -static-libgcc
    )
    
    # 强制使用C++17 ABI
    target_compile_definitions(LogModule PRIVATE
        -D_GLIBCXX_USE_CXX11_ABI=1
    )
endif()