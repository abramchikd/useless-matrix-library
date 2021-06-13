#ifndef HOMEWORK_MATRIX_ROW_HPP
#define HOMEWORK_MATRIX_ROW_HPP

#include <vector>
#include <stdexcept>

namespace mat {

template<class T>
class matrix_row {
  private:
    size_t width;
    std::vector<T> data;

  public:
    explicit matrix_row(size_t width);
    matrix_row(std::initializer_list<T> data);
    ~matrix_row() = default;

    matrix_row(matrix_row<T> const &other);
    matrix_row(matrix_row<T> &&other) = delete;

    auto get_width() -> size_t;

    auto operator=(matrix_row<T> const &other) -> matrix_row<T> &;
    auto operator=(matrix_row<T> &&other) = delete;

    auto operator[](size_t pos) -> T;
};
}

#endif // HOMEWORK_MATRIX_ROW_HPP
