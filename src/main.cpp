#include <iostream>

#include "matrix/matrix_row.hpp"

int main() {
    mat::matrix_row<int> a(3);
    std::cout << a[0];
    return 0;
}