cmake_minimum_required(VERSION 3.10.1)
project(apcpp)

# Compiler flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Werror -Wall -Wextra -Wno-c++98-compat -Wno-unused-parameter -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Werror -Wall -Wextra -Wno-c++98-compat -pedantic-errors")

# Where to look for header files
include_directories(src/)

# This allows "make install" to put all the headers in the right place.
set(APCPP_LIB_HEADERS
    src/apcpp/ap_solver.h
    src/apcpp/primal_dual_ap_solver.h)

set(APCPP_LIB_SOURCES
    src/tsppd/ap/ap_solver.cpp
    src/tsppd/ap/primal_dual_ap_solver.cpp)

# apcpp library
add_library(apcpp SHARED ${APCPP_LIB_SOURCES})
target_link_libraries(apcpp)

# ap test executable
set(APCPP_TEST_SOURCES src/apcpp-test/main.cpp)
add_executable(apcpp-test ${TSPPD_BIN_SOURCES})
target_link_libraries(apcpp-test apcpp)
set_target_properties(apcpp-test PROPERTIES OUTPUT_NAME apcpp-test)
