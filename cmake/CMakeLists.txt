cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Game)

find_package(SDL3 REQUIRED)

set(GM_SRC ${CMAKE_BINARY_DIR}/../src)

set(GAME_SRC    ${GM_SRC}/main.cpp      ${GM_SRC}/Game.cpp
                ${GM_SRC}/Player.cpp    ${GM_SRC}/Math/Vector2.cpp)

add_executable(Game ${GAME_SRC})
target_link_libraries(Game PRIVATE SDL3::SDL3)