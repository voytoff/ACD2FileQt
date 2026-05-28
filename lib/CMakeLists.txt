cmake_minimum_required(VERSION 3.20)
project(ACD2File LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
  Core
)

set(GLOBALLIBDIR "../../GlobalLibQt")
include_directories(${GLOBALLIBDIR})
if (NOT TARGET GlobalLib)
    add_subdirectory(${GLOBALLIBDIR} GlobalLib)
endif()

add_library(ACD2File SHARED
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
)

target_link_libraries(ACD2File PRIVATE
  Qt6::Core
  GlobalLib
)
target_compile_definitions(ACD2File PUBLIC ACD2FILE_LIBRARY)
