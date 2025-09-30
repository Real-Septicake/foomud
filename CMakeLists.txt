cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

project(foomud)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

include(FetchContent)

FetchContent_Declare(enchantum
    GIT_REPOSITORY "https://github.com/ZXShady/enchantum"
    GIT_TAG main
)
FetchContent_MakeAvailable(enchantum)

FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)
FetchContent_MakeAvailable(lexy)

file(GLOB_RECURSE SRC
    ./src/*.cpp
    ./src/**/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${enchantum_SOURCE_DIR}/enchantum/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE foonathan::lexy foonathan::lexy::ext)
