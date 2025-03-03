cmake_minimum_required(VERSION 3.10)
project(CMake_Logging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_library(LoggingModule SHARED ${SRC_LIST})
target_include_directories(LoggingModule PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} LoggingModule)
