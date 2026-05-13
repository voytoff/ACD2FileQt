cmake_minimum_required(VERSION 3.17)
project(tst_ACD2File VERSION 0.1 LANGUAGES CXX)
enable_testing()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test)
qt_standard_project_setup(REQUIRES 6.5)

include_directories(../lib)

set(CMAKE_AUTOMOC ON)

qt_add_executable(tst_ACD2File
    tst_acd2test.cpp
)

#set_target_properties(tst_ACD2File PROPERTIES
#    MACOSX_BUNDLE FALSE
#    WIN32_EXECUTABLE FALSE
#)

target_link_libraries(tst_ACD2File PRIVATE Qt6::Test ACD2File)

add_test(NAME ACD2Test COMMAND ACD2Test)
