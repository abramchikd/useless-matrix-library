#ifndef HOMEWORK_MATRIX_ROW_HPP
#define HOMEWORK_MATRIX_ROW_HPP

namespace mat {

template <class T,
    typename =
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class matrix_row {
  private:
    std::vector<T> data;

  public:
    matrix_row(int width);
    matrix_row(std::initializer_list<T>);
    ~matrix_row() = default;

    matrix_row(matrix_row const& other);
    matrix_row(matrix_row &&other) = delete;

    auto operator=(matrix_row const &other) -> matrix_row<T>;
    auto operator=(matrix_row &&other) = delete;

    auto operator[](size_t pos) -> T;
};
} // namespace mat

#endif // HOMEWORK_MATRIX_ROW_HPP
