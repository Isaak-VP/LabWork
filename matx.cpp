#include "matx.h"
#include <stdexcept>
#include <iostream>

matx::matx() {}

matx::matx(int rows, int cols) {
    matrix.resize(rows, std::vector<num>(cols));
}

matx matx::operator+(const matx& other) const {
    checkSize(other);
    matx result(matrix.size(), matrix[0].size());
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

matx matx::operator-(const matx& other) const {
    checkSize(other);
    matx result(matrix.size(), matrix[0].size());
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}

matx matx::operator*(const matx& other) const {
    if (matrix[0].size() != other.matrix.size()) {
        throw std::invalid_argument("Не можна множити матриці різного розміру");
    }
    matx result(matrix.size(), other.matrix[0].size());
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < other.matrix[0].size(); ++j) {
            num sum = std::string("0");
            for (std::size_t k = 0; k < matrix[0].size(); ++k) {
                sum = sum + (matrix[i][k] * other.matrix[k][j]);
            }
            result.matrix[i][j] = sum;
        }
    }
    return result;
}

matx matx::operator/(const matx& other) const {
    checkSize(other);
    matx result(matrix.size(), matrix[0].size());
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            result.matrix[i][j] = matrix[i][j] / other.matrix[i][j];
        }
    }
    return result;
}

matx& matx::operator=(const matx& other) {
    if (this == &other) return *this;
    this->matrix = other.matrix;
    return *this;
}

bool matx::operator==(const matx& other) const {
    if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
        return false;
    }
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool matx::operator!=(const matx& other) const {
    return !(*this == other);
}

bool matx::operator<(const matx& other) const {
    checkSize(other);
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] < other.matrix[i][j]) {
                return true;
            } else if (matrix[i][j] > other.matrix[i][j]) {
                return false;
            }
        }
    }
    return false;
}

bool matx::operator<=(const matx& other) const {
    return (*this < other || *this == other);
}

bool matx::operator>(const matx& other) const {
    return !(*this <= other);
}

bool matx::operator>=(const matx& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const matx& mtx) {
    for (const auto& row : mtx.matrix) {
        for (const auto& element : row) {
            os << element << " ";
        }
        os << std::endl;
    }
    return os;
}

void matx::checkSize(const matx& other) const {
    if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
        throw std::invalid_argument("Матриці мають різний розмір");
    }
}
