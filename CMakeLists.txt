cmake_minimum_required(VERSION 3.16)
project(EmbeddedCStaticAnalyzer VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)
qt_standard_project_setup()
qt_add_executable(EmbeddedCStaticAnalyzer
    src/main.cpp src/mainwindow.cpp src/analysiscontroller.cpp
    include/mainwindow.h include/analysiscontroller.h include/finding.h)
target_include_directories(EmbeddedCStaticAnalyzer PRIVATE include)
target_compile_options(EmbeddedCStaticAnalyzer PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(EmbeddedCStaticAnalyzer PRIVATE Qt6::Widgets Qt6::Concurrent)
install(TARGETS EmbeddedCStaticAnalyzer RUNTIME DESTINATION bin)
