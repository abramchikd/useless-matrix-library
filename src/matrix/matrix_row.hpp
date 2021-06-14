#ifndef USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP
#define USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

namespace mat {

/**
 * represents a row of matrix
 * @tparam T must support *, /, +, - operations. Correct work is guaranteed only with numeric types, but you can try others on your own risk
 */
template<class T>
class matrix_row {
  private:
    /**
     * width of the row
     */
    size_t width;
    /**
     * elements of the row
     */
    std::vector<T> data;

  public:
    /**
     * fills matrix_row with zeroes
     * @param _width
     */
    explicit matrix_row(size_t _width);
    /**
     * fills matrix row with passed data
     * @param _data
     */
    matrix_row(std::initializer_list<T> _data);

    /**
     * default destructor
     */
    ~matrix_row() = default;

    /**
     * copy constructor
     * @param other
     */
    matrix_row(matrix_row<T> const &other);

    /**
     * width of the matrix
     * @return
     */
    [[nodiscard]]
    auto get_width() const -> size_t;

    /**
     * copy assigment
     * @param other
     * @return
     */
    auto operator=(matrix_row<T> const &other) -> matrix_row<T> &;
    auto operator=(matrix_row<T> &&other) = delete;

    /**
     *
     * @param pos
     * @return element of the row at pos
     */
    auto operator[](size_t pos) -> T &;
    /**
     *
     * @param pos
     * @return element of the row at pos
     */
    auto operator[](size_t pos) const -> T;
};
}

/**
 * output operator
 * @tparam T
 * @param os
 * @param row
 * @return
 */
template <class T>
auto operator<<(std::ostream &os, mat::matrix_row<T> const &row) -> std::ostream &;

#include "matrix_row.inl"

#endif // USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP
