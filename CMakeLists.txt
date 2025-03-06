cmake_minimum_required(VERSION 3.0)
project(MsFuzzyP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libraries/stdexec)
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE STDEXEC::stdexec)