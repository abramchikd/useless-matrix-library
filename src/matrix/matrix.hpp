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
    matrix(matrix<T> const &other);
    matrix(matrix<T> &&other) = delete;

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

    matrix<T> &operator=(matrix<T> const &other);
    matrix<T> &operator=(matrix<T> &&other) = delete;
    auto operator*(matrix<T> const &other) -> matrix<T>;
    auto operator*(double multiplier) -> matrix<T>;
    template <class K>
    friend auto operator*(double multiplier, matrix<K> const &matr) -> matrix<K>;
    auto operator/(double multiplier) -> matrix<T>;
    template <class K>
    friend auto operator/(double multiplier, matrix<K> const &matr) -> matrix<K>;
};

template <class T> auto zero_matrix(size_t width, size_t height) -> matrix<T>;

template <class T> auto unit_matrix(size_t width, size_t height) -> matrix<T>;

} // namespace mat

#endif // HOMEWORK_MATRIX_HPP
