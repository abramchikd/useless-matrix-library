#ifndef USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP
#define USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

namespace mat {

template<class T>
class matrix_row {
  private:
    size_t width;
    std::vector<T> data;

  public:
    explicit matrix_row(size_t _width);
    matrix_row(std::initializer_list<T> _data);
    ~matrix_row() = default;

    matrix_row(matrix_row<T> const &other);

    [[nodiscard]]
    auto get_width() const -> size_t;

    auto operator=(matrix_row<T> const &other) -> matrix_row<T> &;
    auto operator=(matrix_row<T> &&other) = delete;

    auto operator[](size_t pos) -> T &;
    auto operator[](size_t pos) const -> T;
};
}

template <class T>
auto operator<<(std::ostream &os, mat::matrix_row<T> const &row) -> std::ostream &;

#include "matrix_row.inl"

#endif // USELESS_MATRIX_LIBRARY_MATRIX_ROW_HPP
