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
#include <unistd.h>

using namespace std;

pthread_mutex_t mu;

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
        data->resultReference->data(data->currentRow, i) = (data->dataThis[data->columnL * data->currentRow + i]) + (data->dataOther[data->columnL * data->currentRow + i]);
    }
    pthread_exit(NULL);
}

Matrix Matrix::operator+(const Matrix &other)const {
    if (_rows != other._rows || _columns != other._columns) {
        throw "Illegal Argument Exception";
    }
    pthread_t threads[_rows];

    pthread_attr_t att;
    pthread_attr_init(&att);
    pthread_attr_setdetachstate(&att, PTHREAD_CREATE_JOINABLE);

    ThreadData threadStructs[_rows];

    Matrix result(_rows, _columns);

    for (int i = 0; i < _rows; i++) {
        threadStructs[i].currentRow = i;
        threadStructs[i].rowL = _rows;
        threadStructs[i].rowL = other._rows;
        threadStructs[i].columnL = _columns;
        threadStructs[i].columnR = other._columns;
        threadStructs[i].dataThis = _data;
        threadStructs[i].dataOther = other._data;
        threadStructs[i].resultReference = &result;
        pthread_create(&threads[i], &att, &add_thread, (void*) &threadStructs[i]);
    }
    int k;
    for (int i = 0; i < _rows; i++) {
        pthread_join(threads[i], (void**) &k);
    }
    pthread_attr_destroy(&att);
    return result;
}

void *multiply_thread(void *arg) {
    struct ThreadData *data = (struct ThreadData*) arg;
//    pthread_mutex_lock(&mu);
    for (int k = 0; k < data->columnL; k++) {
        data->resultReference->data(data->currentRow, data->currentColumn) +=
                (data->dataThis[data->columnL * data->currentRow + k]) *
                (data->dataOther[k * data->columnR] + data->currentColumn);
    }
//    pthread_mutex_unlock(&mu);
    pthread_exit(NULL);
}

Matrix Matrix::operator*(const Matrix &other)const {
    if (_columns != other._rows) {
        throw "Illegal Argument Exception";
    }
    pthread_attr_t att;
    pthread_attr_init(&att);
    pthread_attr_setdetachstate(&att, PTHREAD_CREATE_JOINABLE);

    pthread_t threads[_rows * other._columns];

    ThreadData threadStructs[_rows * other._columns];

    Matrix result(_rows, other._columns);

//    pthread_mutex_init(&mu, 0);
    
    int counter = 0;

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            threadStructs[counter].currentRow = i;
            threadStructs[counter].rowL = _rows;
            threadStructs[counter].rowR = _columns;
            threadStructs[counter].columnL = _columns;
            threadStructs[counter].columnR = other._columns;
            threadStructs[counter].currentColumn = j;
            threadStructs[counter].dataThis = _data;
            threadStructs[counter].dataOther = other._data;
            threadStructs[counter].resultReference = &result;
            pthread_create(&threads[counter], &att, &multiply_thread, (void*) &threadStructs[counter]);
            counter++;
        }
    }
    pthread_attr_destroy(&att);

        for (int i = 0; i < _rows * other._columns; i++) {
            pthread_join(threads[i], NULL);
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