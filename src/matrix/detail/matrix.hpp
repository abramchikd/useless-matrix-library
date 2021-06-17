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

    return *this;
}
template <class T> auto mat::matrix<T>::t() const -> mat::matrix<T> {
    auto new_matrix = mat::matrix<T>(this->height, this->width);

    for (size_t i = 0; i < this->get_height(); i++) {
        for (size_t j = 0; j < this->get_width(); j++) {
            new_matrix[j][i] = (*this)[i][j];
        }
    }

    return new_matrix;
}
template <class T> auto mat::matrix<T>::determinant() const -> T {
    if (this->get_width() != this->get_height()) {
        throw std::invalid_argument(
            "Determinant is available only for square matrix");
    }

    if (this->get_width() == 1 && this->get_height() == 1) {
        return (*this)[0][0];
    }

    T det = 0;
    for (size_t i = 0; i < this->get_width(); i++) {
        int multiplier = i % 2 == 0 ? 1 : -1;
        det += multiplier * (*this)[0][i] * this->cut(0, i).determinant();
    }

    return det;
}
template <class T>
auto mat::matrix<T>::cut(size_t row, size_t column) const -> mat::matrix<T> {
    auto new_matrix =
        mat::matrix<T>(this->get_width() - 1, this->get_width() - 1);
    size_t new_i = 0;
    for (size_t i = 0; i < this->get_height(); i++) {
        if (i == row) {
            continue;
        }

        size_t new_j = 0;
        for (size_t j = 0; j < this->get_width(); j++) {
            if (j == column) {
                continue;
            }

            new_matrix[new_i][new_j] = (*this)[i][j];
            new_j++;
        }

        new_i++;
    }

    return new_matrix;
}
template <class T>
mat::matrix<T>::matrix(mat::matrix<T> &&other) noexcept
    : width(other.width), height(other.height), data(other.data) {}

template <class T> auto mat::matrix<T>::minor_matrix() const -> mat::matrix<T> {
    auto new_matrix = mat::matrix<T>(this->get_width(), this->get_height());

    for (size_t i = 0; i < this->get_height(); i++) {
        for (size_t j = 0; j < this->get_width(); j++) {
            new_matrix[i][j] = this->cut(i, j).determinant();
        }
    }

    return new_matrix;
}

template <class T>
mat::matrix<T> &mat::matrix<T>::operator=(mat::matrix<T> &&other) noexcept {
    if (this == &other)
        return *this;

    this->width = other.get_width();
    this->height = other.get_height();
    this->data = other.data;

    return *this;
}
template <class T> auto mat::matrix<T>::inverted() const -> mat::matrix<T> {
    auto det = this->determinant();
    auto this_t = this->t();
    auto res = this_t.minor_matrix();
    for (size_t i = 0; i < res.get_height(); i++) {
        for (size_t j = 0; j < res.get_width(); j++) {
            int multiplier = (i + j) % 2 == 0 ? 1 : -1;
            res[i][j] = res[i][j] * multiplier / det;
        }
    }

    return res;
}

template <class T>
auto mat::matrix<T>::operator*(mat::matrix<T> const &other) const
    -> mat::matrix<T> {
    if (this->get_width() != other.get_height()) {
        throw std::invalid_argument(
            "Matrix a and b can be multiplied only if a.height a b.width");
    }

    auto res = mat::matrix<T>(this->get_height(), other.get_width());

    for (size_t i = 0; i < res.get_height(); i++) {
        for (size_t j = 0; j < res.get_width(); j++) {
            res[i][j] = 0;
            for (size_t k = 0; k < this->get_width(); k++) {
                res[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }

    return res;
}
template <class T>
auto mat::matrix<T>::operator*(double multiplier) const -> mat::matrix<T> {
    auto res(*this);

    for (size_t i = 0; i < res.get_height(); i++) {
        for (size_t j = 0; j < res.get_width(); j++) {
            res[i][j] *= multiplier;
        }
    }

    return res;
}

template <class T>
auto mat::matrix<T>::operator/(double multiplier) const -> mat::matrix<T> {
    auto res(*this);

    for (size_t i = 0; i < res.get_height(); i++) {
        for (size_t j = 0; j < res.get_width(); j++) {
            res[i][j] /= multiplier;
        }
    }

    return res;
}
template <class K>
auto operator==(const mat::matrix<K> &left, mat::matrix<K> const &right)
    -> bool {
    if (left.get_width() != right.get_width() ||
        left.get_height() != right.get_height()) {
        return false;
    }

    for (size_t i = 0; i < left.get_height(); i++) {
        for (size_t j = 0; j < right.get_width(); j++) {
            if (left[i][j] != right[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template <class K>
auto operator!=(mat::matrix<K> const &left, mat::matrix<K> &right) -> bool {
    return !(left == right);
}

template <class K>
auto operator*(double multiplier, mat::matrix<K> const &matr)
    -> mat::matrix<K> {
    return matr * multiplier;
}

template <typename T>
auto operator<<(std::ostream &os, mat::matrix<T> const &matrix)
    -> std::ostream & {
    for (size_t i = 0; i < matrix.get_height(); i++) {
        os << "| " << matrix[i] << "|\n";
    }

    return os;
}

template <class T>
auto mat::zero_matrix(size_t width, size_t height) -> mat::matrix<T> {
    return mat::matrix<T>(width, height);
}

template <class T> auto mat::unit_matrix(size_t width) -> mat::matrix<T> {
    auto matrix = mat::matrix<T>(width, width);

    for (size_t i = 0; i < width; i++) {
        matrix[i][i] = 1;
    }

    return matrix;
}