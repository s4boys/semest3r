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
#include <pthread.h>
#include <iostream>

using namespace std;

Matrix::Matrix(int rows, int columns): _rows(rows), _columns(columns) 
{
    _data = new double[_rows*_columns];
}

Matrix::Matrix(const Matrix& other): _rows(other._rows), _columns(other._columns) {
    _data = new double(_rows*_columns);
    memcpy(_data, other._data, _rows*_columns*sizeof(double));
}

Matrix::~Matrix() 
{
    delete [] _data;
}

Matrix Matrix::operator +(const Matrix &other)const 
{
    if ( _rows != other._rows || _columns != other._columns ) {
        throw "Illegal Argument Exception";
    }
    Matrix result(_rows, _columns);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            result.data(i, j) = data(i, j) + other.data(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator *(const Matrix &other)const
{
    if ( _columns != other._rows ) {
        throw "Illegal Argument Exception";
    }
    Matrix result(_rows, other._columns);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            for (int k = 0; k < _columns; k++) {
                result.data(i, j) += data(i, k) * other.data(k, j);
            }
        }
    }
    return result;
}

void * Matrix::thread_function(void * pv)
{
  ThreadData ps =* (ThreadData*) pv;
//  return (void*) ope   Matrix::operator *((Matrix *) pv);
  return ((void *) (ps * this));
}

void Matrix::print() const 
{
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            cout << data(i, j) << " ";
        }
        cout << endl;
    }
}