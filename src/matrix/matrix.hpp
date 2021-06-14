#ifndef USELESS_MATRIX_LIBRARY_MATRIX_HPP
#define USELESS_MATRIX_LIBRARY_MATRIX_HPP

#include "matrix_row.hpp"

namespace mat {

template <class T>
class matrix {
    size_t width;
    size_t height;
    std::vector<matrix_row<T>> data;

  public:
    matrix(size_t _width, size_t _height);
    matrix(std::initializer_list<mat::matrix_row<T>> _data);
    matrix(matrix<T> const &other);
    matrix(matrix<T> &&other) noexcept;

    auto cut(size_t row, size_t column) -> matrix<T>;

    [[nodiscard]]
    auto get_width() const -> size_t;
    [[nodiscard]]
    auto get_height() const -> size_t;

    [[nodiscard]]
    auto t() -> matrix<T>;
    [[nodiscard]]
    auto determinant() -> T;
    [[nodiscard]]
    auto inverted() -> matrix<T>;
    [[nodiscard]]
    auto minor_matrix() -> matrix<T>;
    auto solve();
    // auto characterystical(); //характеристический многочлен
    // auto spectre(); //спектр
    // auto kernel();
    // auto image(); // образ
    // auto svd();
    // auto polar();

    matrix<T> &operator=(matrix<T> const &other);
    matrix<T> &operator=(matrix<T> &&other) noexcept ;
    auto operator*(matrix<T> const &other) -> matrix<T>;
    auto operator*(double multiplier) -> matrix<T>;
    template <class K>
    friend auto operator*(double multiplier, matrix<K> const &matr) -> matrix<K>;
    auto operator/(double multiplier) -> matrix<T>;
    template <class K>
    friend auto operator/(double multiplier, matrix<K> const &matr) -> matrix<K>;

    auto operator[](size_t row_num) -> mat::matrix_row<T> &;
    auto operator[](size_t row_num) const -> mat::matrix_row<T> const &;
};

template <class T> auto zero_matrix(size_t width, size_t height) -> matrix<T>;

template <class T> auto unit_matrix(size_t width, size_t height) -> matrix<T>;

} // namespace mat

template <typename T>
auto operator<<(std::ostream &os, mat::matrix<T> const &matrix) -> std::ostream &;

#include "matrix.inl"

#endif // USELESS_MATRIX_LIBRARY_MATRIX_HPP
