cmake_minimum_required(VERSION 2.8)
project(SpellShecker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -W -Wextra")

set(APP_SOURCES
   ./main.cpp
   ./SpellChecker.cpp
)

add_executable(${PROJECT_NAME}
    ${APP_SOURCES}
)










