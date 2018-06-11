/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: Peter Heusch
 *
 * Created on 31. Mai 2018, 19:32
 */

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    ~Matrix();
    Matrix &operator=(const Matrix &other) = delete;
    Matrix operator +(const Matrix &other)const;
    Matrix operator *(const Matrix &other)const;
    void print() const;
    double &data(int row, int column) {
        return _data[row*_columns+column];
    }
    const double &data(int row, int column)const {
        return _data[row*_columns+column];
    }
    int rows()const {
        return _rows;
    }
    int columns()const {
        return _rows;
    }
    void * thread_function(void * pv);
    
private:
    int _rows;
    int _columns;
    double *_data;
};

struct ThreadData {
    int row;
};
#endif /* MATRIX_H */

