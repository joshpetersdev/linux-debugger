cmake_minimum_required(VERSION 3.19)

project("linux-debugger" LANGUAGES CXX)

include(CTest)

add_subdirectory("src")
add_subdirectory("tools")

if(BUILD_TESTING)
  add_subdirectory("tests")
endif()

add_library(libldb libldb.cpp)
add_library(ldb::libldb ALIAS libldb)

set_target_properties(
  libldb
  PROPERTIES OUTPUT_NAME ldb
)

target_compile_features(libldb PUBLIC cxx_std_17)

target_include_directories(
  libldb
  PRIVATE include
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)
