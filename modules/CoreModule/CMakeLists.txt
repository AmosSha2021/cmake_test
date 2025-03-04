# 创建动态库
add_library(CoreModule SHARED
    src/Calculate.cpp
)

# 设置头文件路径
target_include_directories(CoreModule PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 设置动态库属性
set_target_properties(CoreModule PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    CXX_STANDARD 17
)

# 定义模块导出宏
target_compile_definitions(CoreModule PRIVATE
    CORE_MODULE_EXPORTS
)

# 链接数学库（Linux需要）
if(UNIX)
    target_link_libraries(CoreModule PRIVATE m)
endif()
