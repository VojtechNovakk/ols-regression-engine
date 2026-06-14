#pragma once

#include <stdexcept>
#include <vector>
#include <cstddef>
#include <cmath>

class Matrix {
private:
    size_t m_Rows;
    size_t m_Cols;
    std::vector<double> m_Values;
public:
    Matrix(size_t r, size_t c) : m_Rows(r), m_Cols(c), m_Values(r*c, 0.0) {}
    ~Matrix() = default;
    Matrix(const Matrix& other) : m_Rows(other.m_Rows), m_Cols(other.m_Cols), m_Values(other.m_Values) {}
    Matrix& operator=(Matrix other) {
        std::swap(m_Rows, other.m_Rows);
        std::swap(m_Cols, other.m_Cols);
        std::swap(m_Values, other.m_Values);
        return *this;
    }
    size_t rows() const { return m_Rows; }
    size_t cols() const { return m_Cols; }
    double& operator()(const size_t r, const size_t c) {
        if (r >= m_Rows || c >= m_Cols)
            throw std::out_of_range("Cannot find value with this index!");
        return m_Values[m_Cols*r+c];
    }
    const double& operator()(const size_t r, const size_t c) const{
        if (r >= m_Rows || c >= m_Cols)
            throw std::out_of_range("Cannot find value with this index!");
        return m_Values[m_Cols*r+c];
    }
    double columnNormalization(const size_t c) const {
        if (c >= m_Cols)
            throw std::out_of_range("Cannot find column with this index!");
        double sum = dotColumns(c, c);
        return std::sqrt(sum);
    }

    double dotColumns(const size_t c1, const Matrix& other, const size_t c2) const {
        if (c1 >= m_Cols || c2 >= other.m_Cols)
            throw std::out_of_range("Cannot find columns with this index!");
        if (m_Rows != other.m_Rows)
            throw std::logic_error("Cannot do this operation with Matrix of different sizes!");
        double sum = 0.0;
        for (size_t r = 0; r < m_Rows; ++r)
            sum += (*this)(r, c1) *  other(r, c2);
        return sum;
    }

    double dotColumns(const size_t c1, const size_t c2) const {
        if (c1 >= m_Cols || c2 >= m_Cols)
            throw std::out_of_range("Cannot find columns with this index!");
        return dotColumns(c1, *this, c2);
    }

    Matrix transpose() const {
        Matrix result(m_Cols, m_Rows);
        for (size_t c = 0; c < m_Cols; ++c) {
            for (size_t r = 0; r < m_Rows; ++r)
                result(c,r) = (*this)(r,c);
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (m_Cols != other.m_Rows)
            throw std::logic_error("Matrix dimensions do not match for multiplication!");
        Matrix result(m_Rows, other.m_Cols);

        for (size_t i = 0; i < m_Rows; ++i) {
            for (size_t k = 0; k < m_Cols; ++k) {
                for (size_t j = 0; j < other.m_Cols; ++j)
                    result(i,j) += (*this)(i, k) * other(k,j);
            }
        }
        return result;
    }
};