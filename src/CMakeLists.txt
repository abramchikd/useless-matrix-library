cmake_minimum_required(VERSION 3.10.0)
add_executable(proj_test test.cpp matrix/matrix.hpp matrix/detail/matrix.hpp matrix/matrix_row.hpp matrix/detail/matrix_row.hpp)
add_library(proj matrix/matrix.hpp matrix/detail/matrix.hpp matrix/matrix_row.hpp matrix/detail/matrix_row.hpp)
target_link_libraries(proj_test PUBLIC doctest::doctest default)
target_link_libraries(proj PUBLIC doctest::doctest default)
doctest_discover_tests(proj_test)