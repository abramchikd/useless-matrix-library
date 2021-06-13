#ifndef HOMEWORK_MATRIX_HPP
#define HOMEWORK_MATRIX_HPP

#include "matrix_row.hpp"

namespace mat {

template <class T>
class matrix {
    size_t width;
    size_t height;
    std::vector<matrix_row<T>> data;

  public:
    matrix(size_t width, size_t height);
    matrix(std::initializer_list<std::initializer_list<T>>);
    matrix(matrix const &other);
    matrix(matrix &&other) = delete;

    auto get_width() -> size_t;
    auto get_height() -> size_t;

    auto t() -> matrix<T>;
    auto determinant() -> T;
    auto inverted() -> matrix<T>;
    auto minor_matrix() -> matrix<T>;
    auto solve();
    // auto characterystical(); //характеристический многочлен
    // auto spectre(); //спектр
    // auto kernel();
    // auto image(); // образ
    // auto svd();
    // auto polar();

    matrix &operator=(matrix const &other);
    matrix &operator=(matrix &&other) = delete;
    auto operator*(matrix const &other) -> matrix<T>;
    auto operator*(double multiplier) -> matrix<T>;
    friend auto operator*(double multiplier, matrix const &matr) -> matrix<T>;
    auto operator/(double multiplier) -> matrix<T>;
    friend auto operator/(double multiplier, matrix const &matr) -> matrix<T>;
};

template <class T> auto zero_matrix(size_t width, size_t height) -> matrix<T>;

template <class T> auto unit_matrix(size_t width, size_t height) -> matrix<T>;

} // namespace mat

#endif // HOMEWORK_MATRIX_HPP
