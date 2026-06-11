#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Matrix.hpp"
#include "Regression.hpp"

#define UNIT_TEST(condition, message) \
    do { \
        if(!(condition)) { \
            std::cout << " [FAIL] " << message << " (Row: " << __LINE__ << " )\n"; \
            return false; \
        } \
    } while (0)

constexpr double EPSILON = 1e-9;

bool testMatrixInit() {
    Matrix m1(3,4);
    UNIT_TEST(m1.rows() == 3, "Number of rows must be 3!");
    UNIT_TEST(m1.cols() == 4, "Number of columns must be 4!");
    UNIT_TEST(std::abs(m1(0, 0)) < EPSILON, "Matrix must be initialized with 0!");
    Matrix m2(m1);
    UNIT_TEST(m2.rows() == 3, "Number of rows must be 3!");
    UNIT_TEST(m2.cols() == 4, "Number of columns must be 4!");
    Matrix m3(1,1);
    m3 = m2;
    UNIT_TEST(m3.rows() == 3, "Number of rows must be 3!");
    UNIT_TEST(m3.cols() == 4, "Number of columns must be 4!");
    return true;
}

bool testMatrixValues() {
    Matrix m1(3,4);
    m1(0,0) = 5.4;
    m1(1,2) = 1.3;
    UNIT_TEST(std::abs(m1(0,0)-5.4) < EPSILON, "Value on m1(0, 0) is 5.4!");
    UNIT_TEST(std::abs(m1(1,2)-1.3) < EPSILON, "Value on m1(1, 2) is 1.3!");
    Matrix m2(m1);
    m2(0,0) = 2.2;
    UNIT_TEST(std::abs(m2(0,0)-2.2) < EPSILON, "Value on m2(0, 0) is 2.2!");
    UNIT_TEST(std::abs(m2(1,2)-1.3) < EPSILON, "Value on m2(1, 2) is 1.3!");
    return true;
}

bool testMatrixBounds() {
    Matrix m1(2,2);
    try {
        m1(2,0) = 4.2;
        UNIT_TEST(false, "There should be std::out_of_range error!");
    }catch (const std::out_of_range& e) {

    }
    return true;
}

bool testDot() {
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,0) = 2.0;
    m1(2,0) = 4.0;
    m1(0,1) = -3.0;
    m1(1,1) = 0.0;
    m1(2,1) = 1.0;
    Matrix m2(m1);

    UNIT_TEST(std::abs(m1.dotColumns(0, 0) - 21) <= EPSILON, "This operation should be 21!");
    UNIT_TEST(std::abs(m1.dotColumns(1,1) - 10) <= EPSILON, "This operation should be 10!");
    UNIT_TEST(std::abs(m1.dotColumns(0,1) - 1) <= EPSILON, "This operation should be 1!");
    UNIT_TEST(std::abs(m1.dotColumns(0, m2, 1) - 1) <= EPSILON, "This operation should be 1!");
    try {
        m1.dotColumns(2,2);
        UNIT_TEST(false, "There should be std::out_of_range error!");
    }catch (const std::out_of_range& e) {}
    try {
        m1.dotColumns(-1,0);
        UNIT_TEST(false, "There should be std::out_of_range error!");
    }catch (const std::out_of_range& e) {}
    return true;
}

bool testColumnNormalization() {
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,0) = 2.0;
    m1(2,0) = 4.0;
    m1(0,1) = -3.0;
    m1(1,1) = 0.0;
    m1(2,1) = 1.0;

    UNIT_TEST(std::abs(m1.columnNormalization(0) - std::sqrt(21)) <= EPSILON, "This normalization should be sqrt(21)!");
    UNIT_TEST(std::abs(m1.columnNormalization(1) - std::sqrt(10)) <= EPSILON, "This normalization should be sqrt(10)!");
    try {
        m1.columnNormalization(2);
        UNIT_TEST(false, "There should be std::out_of_range error!");
    }catch (const std::out_of_range& e) {}
    try {
        m1.columnNormalization(-1);
        UNIT_TEST(false, "There should be std::out_of_range error!");
    }catch (const std::out_of_range& e) {}
    return true;
}

bool testRegression() {
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,0) = 2.0;
    m1(2,0) = 4.0;
    m1(0,1) = -3.0;
    m1(1,1) = 0.0;
    m1(2,1) = 1.0;

    QRDecomposition qr = calculate_QR(m1);
    UNIT_TEST((std::abs(qr.m_Q(0,0) - 1/std::sqrt(21)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_Q(1,0) - 2/std::sqrt(21)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_Q(2,0) - 4/std::sqrt(21)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_Q(0,1) + 64/std::sqrt(4389)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_Q(1,1) + 2/std::sqrt(4389)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_Q(2,1) - 17/std::sqrt(4389)) < EPSILON), "Wrong result!");

    UNIT_TEST((std::abs(qr.m_R(0,0) - std::sqrt(21)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_R(1,0) - 0) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_R(0,1) - 1/std::sqrt(21)) < EPSILON), "Wrong result!");
    UNIT_TEST((std::abs(qr.m_R(1,1) - std::sqrt(4389)/21) < EPSILON), "Wrong result!");
    return true;
}

bool testTranspose() {
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,0) = 2.0;
    m1(2,0) = 4.0;
    m1(0,1) = -3.0;
    m1(1,1) = 0.0;
    m1(2,1) = 1.0;

    m1 = m1.transpose();
    UNIT_TEST(m1.rows() == 2, "Number of rows should be 2!");
    UNIT_TEST(m1.cols() == 3, "Number of cols should be 3!");
    UNIT_TEST(std::abs(m1(0,0) - 1.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(m1(1,0) + 3.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(m1(0,1) - 2.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(m1(1,1) - 0.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(m1(0,2) - 4.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(m1(1,2) - 1.0) < EPSILON, "Value is incorrect!");
    return true;
}

bool testMultiplication() {
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,0) = 2.0;
    m1(2,0) = 4.0;
    m1(0,1) = -3.0;
    m1(1,1) = 0.0;
    m1(2,1) = 1.0;

    Matrix m2(2,2);
    m2(0,0) = 2.0;
    m2(1,0) = 6.0;
    m2(0,1) = -4.0;
    m2(1,1) = 0.0;

    Matrix result = m1 * m2;

    UNIT_TEST(result.rows() == 3, "Number of rows should be 3!");
    UNIT_TEST(result.cols() == 2, "Number of cols should be 2!");
    UNIT_TEST(std::abs(result(0,0) + 16.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(1,0) - 4.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(2,0) - 14.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(0,1) + 4.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(1,1) + 8.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(2,1) + 16.0) < EPSILON, "Value is incorrect!");
    return true;
}

bool testBackSubstitution() {
    Matrix m1(3,3);
    m1(0,0) = 2;
    m1(0,1) = 1;
    m1(0,2) = 4;
    m1(1,1) = -3;
    m1(1,2) = 1;
    m1(2,2) = -1;
    Matrix z(3, 1);
    z(0,0) = 1;
    z(1,0) = 1;
    z(2,0) = 4;
    Matrix result(backSubstitution(m1, z));
    UNIT_TEST(std::abs(result(0,0) - 28.0/3.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(1,0) + 5.0/3.0) < EPSILON, "Value is incorrect!");
    UNIT_TEST(std::abs(result(2,0) + 4.0) < EPSILON, "Value is incorrect!");
    return true;
}

void runAllTests() {
    std::cout << "Running tests!\n";

    int passed = 0;
    int total = 0;
    auto runTest = [&passed, &total](bool (*testFunc)(), const std::string& name) {
        total++;
        std::cout << "Runs: " << name << " ... ";
        if (testFunc()) {
            std::cout << "OK\n";
            passed++;
        }
    };
    runTest(testMatrixInit, "Init Matrix");
    runTest(testMatrixValues, "Matrix Values");
    runTest(testMatrixBounds, "Matrix Bounds");
    runTest(testDot, "Matrix Dot Operation");
    runTest(testColumnNormalization, "Column Normalization");
    runTest(testRegression, "QR decomposition");
    runTest(testTranspose, "Matrix Transpose");
    runTest(testMultiplication, "Matrix Multiplication");
    runTest(testBackSubstitution, "Back Substitution");

    std::cout << "Results: " << passed << " / " << total << "\n";
}

int main() {
    runAllTests();
    return 0;
}