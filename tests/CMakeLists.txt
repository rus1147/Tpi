project(tests)

################################
# Google Test
################################
add_subdirectory(lib/googletest-release-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Nuestros tests
################################

# Los headers de los tests
file(GLOB TEST_HEADERS "*.h")
# Los sources de los tests
file(GLOB TEST_SOURCES "*.cpp")

# Creamos el ejecutable para correr los tests
add_executable(correrTests ${TEST_SOURCES} ${TEST_HEADERS} atleta_tests.cpp competencia_tests.cpp jjoo_tests.cpp
        auxiliares_tests.h)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)
# Necesitamos asociar los archivos del TPI
target_link_libraries(correrTests src)

add_test(correrTests correrTests)