cmake_minimum_required(VERSION 3.0.0)
project(Algorithms VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Add the include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/__tests__)

# Add main.cpp from src directory
add_executable(Algorithms ${SOURCE_DIR}/main.cpp)
add_executable(my_tests ${TESTS_DIR}/test_linked_list.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
