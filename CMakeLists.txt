cmake_minimum_required(VERSION 3.28)

project(foomud)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(enchantum
    GIT_REPOSITORY "https://github.com/ZXShady/enchantum"
    GIT_TAG main
)

FetchContent_MakeAvailable(enchantum)

file(GLOB_RECURSE SRC
    ./src/*.cpp
    ./src/**/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${enchantum_SOURCE_DIR}/enchantum/include
)
