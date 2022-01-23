//
// Created by Admin on 22/9/2021.
//

#include "matrix.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define TOLERANCE 0.000000001

using namespace std;

/**
 * Compare the sizes of two matrices, return true if number of rows and number of columns match
 * each other, else return false.
 * @param rows_left number of rows of the lhs matrix
 * @param columns_left number of columns of the lhs matrix
 * @param rows_right number of rows of the rhs matrix
 * @param columns_right number of columns of the rhs matrix
 * @return whether 2 matrices rows and columns are valid to do calculations between them
 */
inline bool
isMatrixSameSize(const int rows_left, const int columns_left, const int rows_right, const int columns_right) {
    return ((rows_left == rows_right) && (columns_left == columns_right));
}

/**
 * Checks whether two doubles are within range of one another to be considered
 * equals, return true is they do else return false.
 * @param a first number
 * @param b second number
 * @return whether two double can be considered equals
 */
inline bool isWithinTolerance(double a, double b) {
    return fabs(a - b) < TOLERANCE;
}

/**
 * Instantiate an object with default constructor that initializes
 * a 1 x 1 matrix that contains a 0
 */
Matrix::Matrix() {
    numOfRows = 1;
    numOfColumns = 1;
    vector<double> valueVector = {0.0};
    matrix.push_back(valueVector);
}

/**
 * Generates an empty n x n matrix based on the user input n.
 * Example: If the user enter 3 then the matrix will be:
 * 0.0 0.0 0.0
 * 0.0 0.0 0.0
 * 0.0 0.0 0.0
 * a matrix with 3 rows and 3 columns with all 0's
 * @param n size of the matrix
 */
Matrix::Matrix(const int n) {
    if (n <= 0) {
        throw "You cannot create a matrix with zero or negative rows or columns";
    }
    numOfRows = n;
    numOfColumns = n;
    vector<double> valueVector(n, 0.0);
    for (int i = 0; i < n; i++) {
        matrix.push_back(valueVector);
    }

}

/**
 * Generates an empty r x c matrix based on the user input r (row) and c (column).
 * Example: If the user enter 3, 4 then the matrix will be:
 * 0.0 0.0 0.0 0.0
 * 0.0 0.0 0.0 0.0
 * 0.0 0.0 0.0 0.0
 * a matrix with 3 rows and 4 columns with all 0's
 * @param n size of the matrix
 */
Matrix::Matrix(const int r, const int c) {
    if (r <= 0 || c <= 0) {
        throw "You cannot create a matrix with zero or negative rows or columns";
    }
    numOfRows = r;
    numOfColumns = c;
    vector<double> valueVector(c, 0.0);
    for (int i = 0; i < r; i++) {
        matrix.push_back(valueVector);
    }
}

/**
 * Turns an array of double to a matrix. The size of the array has
 * to be a perfect square number i.e 1, 4, 9, 16,...
 * @param values an array of double to turn to a matrix
 * @param size size of the array
 */
Matrix::Matrix(const double *values, const int size) {
    // Checks if size is a perfect square number.
    if (size == 0) {
        throw invalid_argument("Unable to generate a matrix from the given input, needs to be a perfect square number.");
    } else if (ceil((double) sqrt(size)) == floor((double) sqrt(size))) {
        int matrixSize = (int) sqrt(size);
        numOfRows = matrixSize;
        numOfColumns = matrixSize;
        vector<double> valueVector;
        // Add items from the array to the matrix
        for (int i = 0; i < size; i++) {
            if (i == 0 || i % matrixSize != 0) {
                valueVector.push_back(values[i]);
                if (i == size - 1) {
                    matrix.push_back(valueVector);
                }
            } else {
                matrix.push_back(valueVector);
                valueVector.clear();
                valueVector.push_back(values[i]);
            }
        }
    } else {
        throw invalid_argument("Unable to generate a matrix from the given input, needs to be a perfect square number.");
    }
}

/**
 * Accepts two integers representing row and column and a double
 * representing the new value for the specified location.
 * Throw an exception if the integers are negative or too large.
 * @param row row index, starts at 0
 * @param column column index, starts at 0
 * @oaram value a double, new value
 */
void Matrix::setValue(const int row, const int column, const double value) {
    if (!isRowAndColumnValid(row, column)) {
        throw invalid_argument("row and column selected must be in range of matrix's size");
    }
    matrix.at(row).at(column) = value;
}

/**
 * Accepts two integers representing row and column
 * and returns the value in the matrix from the specified location.
 * Throw an exception if the integers are negative or too large.
 * @param row row index, starts at 0
 * @param column column index, starts at 0
 * @oaram value a double, new value
 */
double Matrix::getValue(const int row, const int column) const {
    if (!isRowAndColumnValid(row, column)) {
        throw invalid_argument("row and column selected must be in range of matrix's size");
    }
    return matrix.at(row).at(column);
}

/**
 * Sets all values in the matrix to 0.
 */
void Matrix::clear() {
    for (vector<double> &row: matrix) {
        for (double &value: row) {
            value = 0.0;
        }
    }
}

/**
 * Prints out the content of the matrix by overloading the operator <<
 */
std::ostream &operator<<(ostream &os, const Matrix &m) {
    for (const vector<double> &row: m.matrix) {
        for (const double value: row) {
            os << value << " ";
        }
        os << "\n";
    }
    return os;
}

/**
 * Compares two matrix, return true if they have the same size and values.
 */
bool operator==(const Matrix &left, const Matrix &right) {
    if (isMatrixSameSize(left.numOfRows, left.numOfColumns,
                         right.numOfRows, right.numOfColumns)) {
        bool sameValues = false;
        for (int i = 0; i < left.numOfRows; i++) {
            for (int j = 0; j < left.numOfColumns; j++) {
                // Check whether the values are within tolerance of one another
                if (isWithinTolerance(left.matrix.at(i).at(j), right.matrix.at(i).at(j))) {
                    sameValues = true;
                } else {
                    return false;
                }
            }
        }
        return sameValues;
    }
    return false;
}

/**
 * Compares two matrix, return true if they have different values or size.
 */
bool operator!=(const Matrix &left, const Matrix &right) {
    return !(left == right);
}

/**
 * Prefix unary increment, adds 1 to all values of the matrix.
 */
Matrix Matrix::operator++() {
    for (vector<double> &row: matrix) {
        for (double &value: row) {
            value += 1;
        }
    }
    return *this;
}

/**
 * Postfix unary increment, adds 1 to all values of the matrix.
 */
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    operator++();
    return temp;
}

/**
 * Prefix unary decrement, adds 1 from all values of the matrix.
 */
Matrix Matrix::operator--() {
    for (vector<double> &row: matrix) {
        for (double &value: row) {
            value -= 1;
        }
    }
    return *this;
}

/**
 * Postfix unary decrement, subtract 1 from all values of the matrix.
 */
Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    operator--();
    return temp;
}

/**
 * Add matrix lhs and matrix rhs and return the result of the sum.
 */
Matrix operator+(Matrix left, const Matrix &right) {
    if (isMatrixSameSize(left.getNumOfRows(), left.getNumOfColumns(),
                         right.getNumOfRows(), right.getNumOfColumns())) {
        vector<vector<double>> leftMatrix = left.getMatrix();
        vector<vector<double>> rightMatrix = right.matrix;

        Matrix newMatrix(right.numOfRows, right.numOfColumns);

        for (int row = 0; row < right.numOfRows; row++) {
            for (int col = 0; col < right.numOfColumns; col++) {
                newMatrix.setValue(row, col,
                                   leftMatrix.at(row).at(col) + rightMatrix.at(row).at(col));
            }
        }

        return newMatrix;
    } else { throw invalid_argument("The matrices are not the same size"); }
}

/**
 * Subtract matrix lhs and matrix rhs and return the result of the difference, throws exception if
 * 2 matrices are not the same size.
 * @params left lhs matrix
 * @params right rhs matrix
 * @return matrix
 */
Matrix operator-(Matrix left, const Matrix &right) {
    if (isMatrixSameSize(left.getNumOfRows(), left.getNumOfColumns(),
                         right.getNumOfRows(), right.getNumOfColumns())) {
        vector<vector<double>> leftMatrix = left.getMatrix();
        vector<vector<double>> rightMatrix = right.matrix;

        Matrix newMatrix(right.numOfRows, right.numOfColumns);

        for (int row = 0; row < right.numOfRows; row++) {
            for (int col = 0; col < right.numOfColumns; col++) {
                newMatrix.setValue(row, col,
                                   leftMatrix.at(row).at(col) - rightMatrix.at(row).at(col));
            }
        }

        return newMatrix;
    } else { throw invalid_argument("The matrices are not the same size"); }
}

/**
 * Add matrix in the argument to the matrix calling the function, throws exception if
 * 2 matrices are not the same size.
 * @params right rhs matrix
 * @return matrix
 */
Matrix &Matrix::operator+=(const Matrix &right) {
    if (isMatrixSameSize(numOfRows, numOfColumns,
                         right.getNumOfRows(), right.getNumOfColumns())) {
        for (int row = 0; row < right.numOfRows; row++) {
            for (int col = 0; col < right.numOfColumns; col++) {
                matrix.at(row).at(col) += right.matrix.at(row).at(col);
            }
        }
        return *this;
    } else { throw invalid_argument("The matrices are not the same size"); }
}

/**
 * Subtract matrix in the argument from the matrix calling the function, throws exception if
 * 2 matrices are not the same size.
 * @params right rhs matrix
 * @return matrix
 */
Matrix &Matrix::operator-=(const Matrix &right) {
    if (isMatrixSameSize(numOfRows, numOfColumns,
                         right.getNumOfRows(), right.getNumOfColumns())) {
        for (int row = 0; row < right.numOfRows; row++) {
            for (int col = 0; col < right.numOfColumns; col++) {
                matrix.at(row).at(col) -= right.matrix.at(row).at(col);
            }
        }
        return *this;
    } else { throw invalid_argument("The matrices are not the same size"); }
}

/**
 * Multiply 2 matrices, throws exception if they are not compatible for multiplication.
 * @params right rhs matrix
 * @return matrix
 */
Matrix &Matrix::operator*=(const Matrix &right) {
    if (numOfColumns != right.numOfRows) {
        throw invalid_argument("Number of columns of first matrix must be the same as number of rows of the second matrix");
    }
    vector<double> row;
    vector<vector<double>> newMatrix;
    double sum = 0.0;

    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < right.numOfColumns; j++) {
            for (int l = 0; l < numOfColumns; l++) {
                sum += matrix.at(i).at(l) * right.matrix.at(l).at(j);
            }
            row.push_back(sum);
            sum = 0;
        }
        newMatrix.push_back(row);
        row.clear();
    }
    numOfColumns = right.numOfColumns;
    matrix = newMatrix;
    return *this;
}

/**
 * Multiply 2 matrices, throws exception if they are not compatible for multiplication.
 * @params left lhs matrix
 * @params right rhs matrix
 * @return matrix
 */
Matrix operator*(Matrix left, const Matrix &right) {
    if (left.getNumOfColumns() != right.numOfRows) {
        throw invalid_argument("Number of columns of first matrix must be the same as number of rows of the second matrix");
    }
    left *= right;

    return left;
}

/**
 * Assignment operator
 * @param rhs matrix to copy
 * @return changed original matrix
 */
Matrix &Matrix::operator=(Matrix &rhs) {
    using std::swap;
    swap((*this).numOfColumns, rhs.numOfColumns);
    swap((*this).numOfRows, rhs.numOfRows);
    swap((*this).matrix, rhs.matrix);
    return *this;
}

/**
 * Copy constructor for matrix class.
 * @params rhs matrix
 * @return matrix
 */
Matrix::Matrix(const Matrix &rhs) {
    (*this).numOfColumns = rhs.numOfColumns;
    (*this).numOfRows = rhs.numOfRows;
    (*this).matrix = rhs.matrix;
}





