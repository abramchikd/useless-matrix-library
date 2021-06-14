#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#pragma ide diagnostic ignored "readability-magic-numbers"
#include "catch.hpp"

#include <iostream>
#include <valarray>

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

TEST_CASE("matrix transposing") {
    auto matrix = mat::matrix<int> {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto matrix_t = matrix.t();

    CHECK(matrix_t.get_width() == matrix.get_height());
    CHECK(matrix_t.get_height() == matrix.get_width());

    for (size_t i = 0; i < matrix.get_height(); i++) {
        for (size_t j = 0; j < matrix.get_width(); j++) {
            CHECK(matrix_t[j][i] == matrix[i][j]);
        }
    }
}

TEST_CASE("throws on attempt to find determinant of non-square matrix") {
    auto matrix = mat::matrix<int>(3, 4);
    CHECK_THROWS((void) matrix.determinant());
}

TEST_CASE("matrix::cut") {
    auto matrix = mat::matrix<int> {{1, 2}, {3, 4}};
    auto m = matrix.cut(0, 0);
    CHECK(m[0][0] == 4);
    auto m2 = matrix.cut(0, 1);
    CHECK(m2[0][0] == 3);
}

TEST_CASE("determinant") {
    auto matrix = mat::matrix<double> {{1.0, 0, 0},
                                    {0, sqrt(2)/2, -sqrt(2)/2},
                                      {0, sqrt(2)/2, sqrt(2)/2}};
    CHECK((matrix.determinant() - 1.0) < 1e-9);
}

TEST_CASE("Minor matrix") {
    auto matrix = mat::matrix<int> {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto result = mat::matrix<int> {{-3, -6, -3}, {-6, -12, -6}, {-3, -6, -3}};

    matrix = matrix.minor_matrix();

    for (size_t i = 0; i < matrix.get_height(); i++) {
        for (size_t j = 0; j < matrix.get_width(); j++) {
            CHECK(matrix[i][j] == result[i][j]);
        }
    }
}

TEST_CASE("Inverted matrix") {
    auto matrix = mat::matrix<double> {{2, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto res = mat::matrix<double> {{1, -2, 1}, {-2, 1, 0}, {1, 2.0/3, -2.0/3}};

    auto m = matrix.inverted();

    for (size_t i = 0; i < m.get_height(); i++) {
        for (size_t j = 0; j < m.get_width(); j ++) {
            CHECK(std::abs(m[i][j] - res[i][j]) < 1e-9);
        }
    }
}

TEST_CASE("Matrix multiplication throws") {
    auto m1 = mat::matrix<int>(1, 2);
    auto m2 = mat::matrix<int>(3, 4);

    CHECK_THROWS(m1 * m2);
}

TEST_CASE("Matrix multiplication") {
    auto m1 = mat::matrix<int> {{1, 2, 3}, {4, 5, 6}, {7, 8 , 9}};
    auto mat = m1 * m1;

    auto res = mat::matrix<int> {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};

    for (size_t i = 0; i < mat.get_height(); i++) {
        for (size_t j = 0; j < mat.get_width(); j++) {
            CHECK(mat[i][j] == res[i][j]);
        }
    }
}

TEST_CASE("Unit matrix test") {
    auto m = mat::matrix<double>{{2, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    bool eq = mat::unit_matrix<double>(3) == m * m.inverted();
    CHECK(eq);
}
#pragma clang diagnostic pop