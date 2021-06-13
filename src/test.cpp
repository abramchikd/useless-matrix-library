#include "catch.hpp"

#include <iostream>

#include "matrix/matrix.hpp"
#include "matrix/matrix_row.hpp"

TEST_CASE("mat::matrix_row(size_t) constructor test") {
    auto row = mat::matrix_row<int>(3);
    CHECK(row.get_width() == 3);
    for (size_t i = 0; i < 3; i++) {
        CHECK(row[i] == 0);
    }
}

TEST_CASE("mat::matrix_row(std::initializer_list<T>) constructor test") {
    auto row = mat::matrix_row{0, 1, 2, 3};
    CHECK(row.get_width() == 4);
    for (size_t i = 0; i < 4; i++) {
        CHECK(row[i] == i);
    }
}

TEST_CASE("mat::matrix_row throws std::out_of_range exception") {
    auto row = mat::matrix_row<int>(2);
    CHECK_THROWS(row[2]);
    CHECK_THROWS(row[3]);
}

TEST_CASE("mat::matrix(size_t) constructor") {
    auto matrix = mat::matrix<int>(2, 2);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            CHECK(matrix[i][j] == 0);
        }
    }
}

TEST_CASE("mat::matrix(std::initializer_list<...) constructor") {
    auto matrix = mat::matrix<int>{{0, 1}, {1, 2}};

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            CHECK(matrix[i][j] == i + j);
        }
    }
}

TEST_CASE("mat::matrix copy constructor") {
    auto a = mat::matrix<int>{{0, 1}, {1, 2}};
    auto b = a;

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            CHECK(b[i][j] == i + j);
        }
    }
}

TEST_CASE("mat::matrix copy assigment operator") {
    auto a = mat::matrix<int>{{5, 5}, {5, 5}};
    auto b = mat::matrix<int>(2, 2);

    b = a;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            CHECK(b[i][j] == 5);
        }
    }
}

TEST_CASE("mat::matrix throws std::out_of_range exception") {
    auto matrix = mat::matrix<int>(2, 2);
    CHECK_THROWS(matrix[2]);
}