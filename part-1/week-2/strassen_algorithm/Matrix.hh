#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    int **matrix;
    int n;

public:
    Matrix(int n);
    ~Matrix(void);
    void print(void);
    void scan(void);
    int size(void);
    Matrix operator+(Matrix &m);
    Matrix operator-(Matrix &m);
    Matrix operator*(Matrix &m);
    bool operator==(Matrix &m);
    void operator=(Matrix m);
    friend Matrix strassen_multiplication(Matrix &m1, Matrix &m2);
};

#endif
