#include "catch.hpp"

#include "matrix/matrix_row.hpp"

TEST_CASE("mat::matrix_row(int) constructor test") {
    auto row = mat::matrix_row<int>(3);
    CHECK(row.get_width() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(row[i] == 0);
    }
}

TEST_CASE("mat::matrix_row(std::initializer_list<T>) constructor test") {
    auto row = mat::matrix_row {0, 1, 2, 3};
    CHECK(row.get_width() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(row[i] == i);
    }
}

TEST_CASE("mat::matrix std::out_of_range exception") {
    auto row = mat::matrix_row<int>(2);
    CHECK_THROWS(row[2]);
    CHECK_THROWS(row[3]);
}