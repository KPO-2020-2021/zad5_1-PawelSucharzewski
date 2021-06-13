cmake_minimum_required(VERSION 3.16)
project(Dron)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)
add_subdirectory(lib/googletest)

include_directories(inc)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true inc/*.h src/*.cpp)
set(SOURCE ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCE})
