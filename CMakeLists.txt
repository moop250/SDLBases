cmake_minimum_required(VERSION 3.10)

project (SDLTest)

find_package(SDL3 REQUIRED)

include_directories(incl ${SDL3_INCLUDE_DIRS})

add_executable(main srcs/main.cpp srcs/AppState.cpp)

target_link_libraries(main ${SDL3_LIBRARIES})

