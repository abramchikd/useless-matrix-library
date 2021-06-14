#ifndef USELESS_MATRIX_LIBRARY_MATRIX_HPP
#define USELESS_MATRIX_LIBRARY_MATRIX_HPP

#include "matrix_row.hpp"

namespace mat {

template <class T>

/**
 * Represents two-dimensional matrix
 * @tparam T must support *, /, +, - operations. Correct work is guaranteed only
 * with numeric types, but you can try others on your own risk
 */
class matrix {

    /**
     * width of the matrix
     */
    size_t width;
    /**
     * height of the matrix
     */
    size_t height;
    /**
     * rows of the matrix containing it`s elements
     */
    std::vector<matrix_row<T>> data;

  public:
    /**
     * creates matrix filled with zeroes
     * @param _width
     * @param _height
     */
    matrix(size_t _width, size_t _height);

    /**
     * creates matrix by it`s elements
     * @param _data notice that each row must have same width
     */
    matrix(std::initializer_list<mat::matrix_row<T>> _data);

    /**
     * copy constructor
     * @param other
     */
    matrix(matrix<T> const &other);
    /**
     * move constructor
     * @param other
     */
    matrix(matrix<T> &&other) noexcept;

    /**
     * makes a new matrix by cutting row and column from the original away
     * @param row
     * @param column
     * @return matrix of size width - 1 and height - 1
     */
    auto cut(size_t row, size_t column) const -> matrix<T>;

    /**
     *
     * @return width of the matrix
     */
    [[nodiscard]] auto get_width() const -> size_t;
    /**
     *
     * @return height of the matrix
     */
    [[nodiscard]] auto get_height() const -> size_t;

    /**
     * @return transposed matrix
     */
    [[nodiscard]] auto t() const -> matrix<T>;

    /**
     * @attention Be aware of factorial time complexity
     * @return determinant of the matrix
     */
    [[nodiscard]] auto determinant() const -> T;

    /**
     * @return inverted matrix
     */
    [[nodiscard]] auto inverted() const -> matrix<T>;

    /**
     *
     * @return matrix of minors with same size as original
     */
    [[nodiscard]] auto minor_matrix() const -> matrix<T>;

    /**
     * copy assigment
     * @param other
     * @return
     */
    matrix<T> &operator=(matrix<T> const &other);
    /**
     * move assigment
     * @param other
     * @return
     */
    matrix<T> &operator=(matrix<T> &&other) noexcept;

    /**
     * matrix multiplication
     * @param other matrix with width = height of the first matrix
     * @return matrix multiplication
     * @throws std::invalid_argument if other.width != this.height
     */
    auto operator*(matrix<T> const &other) const -> matrix<T>;
    /**
     * multiples each member of the matrix by multiplier
     * @param multiplier
     * @return matrix of same size
     */
    auto operator*(double multiplier) const -> matrix<T>;
    /**
     * multiples each member of the matrix by multiplier
     * @param multiplier
     * @return matrix of same size
     */
    auto operator/(double multiplier) const -> matrix<T>;

    /**
     * @param row_num
     * @return specified row of the matrix
     */
    auto operator[](size_t row_num) -> mat::matrix_row<T> &;

    /**
     * @param row_num
     * @return specified row of the matrix
     */
    auto operator[](size_t row_num) const -> mat::matrix_row<T> const &;
};

/**
 *
 * @tparam T must support *, /, +, - operations. Correct work is guaranteed only
 * with numeric types, but you can try others on your own risk
 * @param width
 * @param height
 * @return matrix of specified width and height filled width zeroes
 */
template <class T> auto zero_matrix(size_t width, size_t height) -> matrix<T>;

/**
 *
 * @tparam T must support *, /, +, - operations. Correct work is guaranteed only
 * with numeric types, but you can try others on your own risk
 * @param width
 * @return unit matrix with specified width and height
 */
template <class T> auto unit_matrix(size_t width) -> matrix<T>;

} // namespace mat

/**
 * multiples each member of the matrix by multiplier
 * @tparam K
 * @param multiplier
 * @param matr
 * @return
 */
template <class K>
auto operator*(double multiplier, mat::matrix<K> const &matr) -> mat::matrix<K>;

/**
 * equal operator
 * @tparam K
 * @param other
 * @return
 */
template <class K>
auto operator==(mat::matrix<K> const &left, mat::matrix<K> const &right)
    -> bool;

/**
 * not-equal operator
 * @tparam K
 * @param other
 * @return
 */
template <class K>
auto operator!=(mat::matrix<K> const &left, mat::matrix<K> &right) -> bool;

/**
 * output operator
 * @tparam T
 * @param os
 * @param matrix
 * @return
 */
template <typename T>
auto operator<<(std::ostream &os, mat::matrix<T> const &matrix)
    -> std::ostream &;

#include "matrix.inl"

#endif // USELESS_MATRIX_LIBRARY_MATRIX_HPP
