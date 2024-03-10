cmake_minimum_required(VERSION 3.27)

project(
  ${CMAKE_PROJECT_NAME}
  DESCRIPTION "Shared Pointer Header Only Lib"
  LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${SP_INCLUDE_DIR})
