cmake_minimum_required(VERSION 3.16)

project(MyShell C)

# Options globales
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -W")

# Debug options
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fsanitize=address -g")

include_directories(include)

file(GLOB SOURCES "src/**.c" "src/builtins/*.c" "src/utils/*.c")

add_executable(mysh ${SOURCES})

