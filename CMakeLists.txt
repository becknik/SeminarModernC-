cmake_minimum_required(VERSION 3.27)

project(SeminarModernCpp VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Add tasks subprojects
#include(cmake/utils.cmake)
#add_subprojects(${CMAKE_SOURCE_DIR})

# Library setup

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
#add_library(fmt SHARED IMPORTED)
#set_target_properties(fmt PROPERTIES IMPORTED_LOCATION /lib/libfmt.so)

# Target setup

add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE nlohmann_json nlohmann_json::nlohmann_json ${CURL_LIBRARIES})