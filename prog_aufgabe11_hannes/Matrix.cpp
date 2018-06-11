/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.cpp
 * Author: Peter Heusch
 * 
 * Created on 31. Mai 2018, 19:32
 */

#include "Matrix.h"
#include <memory.h>
#include <iostream>

using namespace std;

Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
    _data = new double[_rows * _columns];
}

Matrix::Matrix(const Matrix& other) : _rows(other._rows), _columns(other._columns) {
    _data = new double(_rows * _columns);
    memcpy(_data, other._data, _rows * _columns * sizeof (double));
}

Matrix::~Matrix() {
    delete [] _data;
}

void *add_thread(void *arg) {
    struct ThreadData *data = (struct ThreadData*) arg;
    for (int i = 0; i < data->columnL; i++) {
        data->resultReference->data(data->rowL, i) = (data->dataThis[data->columnL * data->rowL + i]) + (data->dataOther[data->columnL * data->rowL + i]);
    }
    pthread_exit(NULL);
}

Matrix Matrix::operator+(const Matrix &other)const {
    if (_rows != other._rows || _columns != other._columns) {
        throw "Illegal Argument Exception";
    }
    pthread_t threads[_rows];

    ThreadData threadStructs[_rows];

    Matrix result(_rows, _columns);

    for (int i = 0; i < _rows; i++) {
        threadStructs[i].rowL = i;
        threadStructs[i].columnL = _columns;
        threadStructs[i].columnR = other._columns;
        threadStructs[i].dataThis = _data;
        threadStructs[i].dataOther = other._data;
        threadStructs[i].resultReference = &result;
        pthread_create(&threads[i], NULL, &add_thread, (void*) &threadStructs[i]);
    }
    return result;
}
//1 0       3 2 1 
//2 3       6 7 8
//4 5 

//    for (int i = 0; i < _rows; i++) {
//        for (int j = 0; j < other._columns; j++) {
//            for (int k = 0; k < _columns; k++) {
//                result.data(i, j) += data(i, k) * other.data(k, j);
//            }
//        }
//    }

void *multiply_thread(void *arg) {
    struct ThreadData *data = (struct ThreadData*) arg;

    data->resultReference->data(data->rowL, data->columnR) =
            (data->dataThis[data->rowL * data->rowL + data->columnR]) + (data->dataOther[data->columnL * data->rowL + i]);

    pthread_exit(NULL);
}

Matrix Matrix::operator*(const Matrix &other)const {
    if (_columns != other._rows) {
        throw "Illegal Argument Exception";
    }
    pthread_t threads[_rows * other._columns];

    ThreadData threadStructs[_rows * other._columns];

    Matrix result(_rows, other._columns);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            threadStructs[i].rowL = i;
            threadStructs[i].columnL = j;
            threadStructs[i].columnR = _columns;
            threadStructs[i].dataThis = _data;
            threadStructs[i].dataOther = other._data;
            threadStructs[i].resultReference = &result;
            pthread_create(&threads[i], NULL, &add_thread, (void*) &threadStructs[i]);
        }
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            for (int k = 0; k < _columns; k++) {
                result.data(i, j) += data(i, k) * other.data(k, j);
            }
        }
    }
    return result;
}

void Matrix::print() const {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            cout << data(i, j) << " ";
        }
        cout << endl;
    }
}