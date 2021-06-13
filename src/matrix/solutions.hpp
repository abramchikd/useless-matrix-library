#ifndef USELESS_MATRIX_LIBRARY_SOLUTIONS_HPP
#define USELESS_MATRIX_LIBRARY_SOLUTIONS_HPP

#include <vector>

namespace mat {

enum class solutions_type {
    infinite, none, finite
};

struct solutions {
    solutions_type type;
    size_t number_of_solutions = -1;
    std::vector<double> sol = {};

    solutions(solutions_type type, size_t number_of_solutions = -1, std::vector<double> const& sol = {});
};
} // namespace mat

#endif // USELESS_MATRIX_LIBRARY_SOLUTIONS_HPP
