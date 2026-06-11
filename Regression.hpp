#pragma once

#include "Matrix.hpp"

struct QRDecomposition {
    Matrix m_Q;
    Matrix m_R;
    QRDecomposition(Matrix q, Matrix r) : m_Q(q), m_R(r) {}
};

QRDecomposition calculate_QR(const Matrix& m) {
    QRDecomposition qr(m, Matrix(m.cols(), m.cols()));
    Matrix& q = qr.m_Q;
    Matrix& r = qr.m_R;
    Matrix v(m);
    for (size_t i = 0; i < m.cols(); ++i) {
        r(i, i) = v.columnNormalization(i);
        for (size_t j = 0; j < m.rows(); ++j)
            q(j,i) = v(j,i) / r(i, i);
        for (size_t j = i + 1; j < m.cols(); ++j) {
            r(i,j ) = q.dotColumns(i, v, j);
            for (size_t k = 0; k < m.rows(); ++k)
                v(k, j) = v(k, j) - r(i,j )*q(k,i);
        }
    }
    return qr;
}

Matrix backSubstitution(const Matrix& R, const Matrix& Z) {
    Matrix result(R.rows(), 1);
    for (size_t i = R.rows()-1; i < R.rows(); --i) {
        double sum = Z(i, 0);
        for (size_t j = i+1; j < R.rows(); ++j)
            sum -= result(j, 0)*R(i,j);
        result(i, 0) = sum / R(i,i);
    }
    return result;
}
