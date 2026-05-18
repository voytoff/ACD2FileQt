cmake_minimum_required(VERSION 3.20)

project(ACD2File LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Core5Compat)
find_package(Qt6 REQUIRED COMPONENTS Core Core5Compat)

add_library(ACD2File SHARED #STATIC
  ACD2File_global.h
  acd2file.h acd2file.cpp
  acdobject.h acdobject.cpp
  channelarray.h channelarray.cpp
  channelblock.h channelblock.cpp
  datablock.h datablock.cpp
  fileitem.h fileitem.cpp
  fileidblock.h fileidblock.cpp
  headerblock.h headerblock.cpp
  hashblock.h hashblock.cpp
  fileacd.h fileacd.cpp
  parameter.h parameter.cpp
  datablockarray.h datablockarray.cpp
  lib.cpp lib.h
)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
target_link_libraries(ACD2File PRIVATE Qt6::Core Qt6::Core5Compat)
target_compile_definitions(ACD2File PRIVATE ACD2FILE_LIBRARY)
