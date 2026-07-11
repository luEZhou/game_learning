cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Game)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

set(GM_SRC ${CMAKE_BINARY_DIR}/../src)

set(Engine_SRC ${GM_SRC}/Engine/Math/Vector2.cpp 
    ${GM_SRC}/Engine/Graphics/Texture2D.cpp
    ${GM_SRC}/Engine/ResourceManager.cpp)

set(GAME_SRC    ${Engine_SRC}       ${GM_SRC}/Brick.cpp
                ${GM_SRC}/Game.cpp  ${GM_SRC}/GameObject.cpp
                ${GM_SRC}/main.cpp  ${GM_SRC}/Paddle.cpp)

add_executable(Game ${GAME_SRC})
target_include_directories(Game PRIVATE ${GM_SRC}/Engine)
target_link_libraries(Game PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

install(TARGETS Game)
install(DIRECTORY ${CMAKE_BINARY_DIR}/../assets DESTINATION ${CMAKE_INSTALL_PREFIX})