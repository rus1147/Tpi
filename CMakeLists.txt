# Minima version de CMake requerida para el proyecto
cmake_minimum_required(VERSION 2.8)

# Nombre del proyecto
project(TPI)

# Algunos flags para pasar al compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -Wall")

# Traemos los headers (*.h) del TPI
include_directories(../include)

# Ahora todos los sources (*.cpp)
file(GLOB SOURCES "src/*.cpp")

add_executable(tpi ${SOURCES})

add_library(src ${SOURCES})

# CMake anda a buscar lo que hay en el directorio 'tests'!
add_subdirectory(tests)