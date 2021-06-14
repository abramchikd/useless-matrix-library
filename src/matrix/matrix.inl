#include "matrix.hpp"

template <class T>
mat::matrix<T>::matrix(size_t _width, size_t _height)
    : width{_width}, height{_height} {
    for (size_t i = 0; i < _height; i++) {
        this->data.emplace_back(mat::matrix_row<T>(_width));
    }
}

template <class T>
mat::matrix<T>::matrix(std::initializer_list<mat::matrix_row<T>> _data)
    : data{_data} {
    this->height = data.size();
    this->width = data.at(0).get_width();
}

template <class T>
mat::matrix<T>::matrix(mat::matrix<T> const &other)
    : width{other.width}, height{other.height}, data{other.data} {}

template <class T>
auto mat::matrix<T>::operator[](size_t row_num) -> mat::matrix_row<T> & {
    if (row_num >= this->height) {
        using namespace std::string_literals;
        throw std::out_of_range("Trying to get "s + std::to_string(row_num) +
                                " row of matrix with height " +
                                std::to_string(this->height));
    }
    return this->data[row_num];
}

template <class T>
auto mat::matrix<T>::operator[](size_t row_num) const
    -> mat::matrix_row<T> const & {
    if (row_num >= this->height) {
        using namespace std::string_literals;
        throw std::out_of_range("Trying to get "s + std::to_string(row_num) +
                                " row of matrix with height " +
                                std::to_string(this->height));
    }
    return this->data[row_num];
}

template <class T> auto mat::matrix<T>::get_width() const -> size_t {
    return this->width;
}

template <class T> auto mat::matrix<T>::get_height() const -> size_t {
    return this->height;
}
template <class T>
mat::matrix<T> &mat::matrix<T>::operator=(mat::matrix<T> const &other) {
    this->width = other.width;
    this->height = other.height;
    this->data = other.data;
}
template <class T>
auto mat::matrix<T>::t() -> mat::matrix<T> {
    auto new_matrix = mat::matrix<T>(this->height, this->width);

    for (int i = 0; i < this->get_height(); i++) {
        for (int j = 0; j < this->get_width(); j++) {
            new_matrix[j][i] = (*this)[i][j];
        }
    }

    return new_matrix;
}

template <typename T>
auto operator<<(std::ostream &os, mat::matrix<T> const &matrix)
    -> std::ostream & {
    for (size_t i = 0; i < matrix.get_height(); i++) {
        os << "| " << matrix[i] << "|\n";
    }

    return os;
}