//
// Created by Admin on 22/9/2021.
//

#ifndef LAB1TEMPLATE_MATRIX_HPP
#define LAB1TEMPLATE_MATRIX_HPP

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<double>> matrix;
    int numOfRows;
    int numOfColumns;
public:
    Matrix();

    Matrix(int);

    Matrix(int, int);

    Matrix(const double *, int);

    Matrix &operator=(Matrix&);

    Matrix(const Matrix&);

    ~Matrix() = default;

    void setValue(int, int, double);

    double getValue(int, int) const;

    void clear();

    int getNumOfRows() const { return numOfRows; }

    int getNumOfColumns() const { return numOfColumns; }

    std::vector<std::vector<double>> getMatrix() const { return matrix; }

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator*=(const Matrix &);

    friend std::ostream &operator<<(std::ostream &, const Matrix &);

    friend bool operator==(const Matrix &, const Matrix &);

    friend bool operator!=(const Matrix &, const Matrix &);

    friend Matrix operator+(Matrix, const Matrix &);

    friend Matrix operator-(Matrix, const Matrix &);

    friend Matrix operator*(Matrix, const Matrix &);

    Matrix operator++();

    Matrix operator++(int); // postfix
    Matrix operator--();

    Matrix operator--(int); //postfix

    inline bool isRowAndColumnValid(const int rows, const int columns) const {
        return !(rows < 0 || rows >= numOfRows
                 || columns < 0 || columns >= numOfColumns);
    }


};

#endif //LAB1TEMPLATE_MATRIX_HPP
