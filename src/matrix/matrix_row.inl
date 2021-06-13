#include "matrix_row.hpp"

#include <string>

template <class T>
mat::matrix_row<T>::matrix_row(size_t _width)
    : width{_width}, data{std::vector(_width, 0)} {}

template <class T>
mat::matrix_row<T>::matrix_row(std::initializer_list<T> _data)
    : width{_data.size()}, data{_data} {}

template <class T>
mat::matrix_row<T>::matrix_row(mat::matrix_row<T> const &other)
    : width{other.width}, data{other.data} {}

template <class T>
auto mat::matrix_row<T>::get_width() -> size_t {
    return this->width;
}

template <class T>
auto mat::matrix_row<T>::operator=(mat::matrix_row<T> const &other) -> mat::matrix_row<T> & {
    this->width = other.width;
    this->data = other.data;

    return *this;
}

template <class T>
auto mat::matrix_row<T>::operator[](size_t pos) -> T {
    if (pos >= data.size()) {
        using namespace std::string_literals;
        throw std::out_of_range("Trying to get "s
                                + std::to_string(pos)
                                + " element of row with size "
                                + std::to_string(this->width));
    }

    return data.at(pos);
}

#include "matrix.inl"
