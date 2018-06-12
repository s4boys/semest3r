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
#include <thread>
#include <vector>
// #include <ref>

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

Matrix Matrix::operator +(const Matrix &other)const {

    if ( _rows != other._rows || _columns != other._columns ) {
        throw "Illegal Argument Exception";
    }
    Matrix result(_rows, _columns);
    std::vector<std::thread> threads;

    for (int i = 0; i < _rows; i++) {
        // threads.push_back(std::thread(addition_worker, i, , , ));
        threads.push_back(std::thread(Matrix::addition_worker, i, _columns, *this, other, std::ref(result)));
    }

    for (auto& th: threads){
        th.join();
        delete &th;
    }

    return result;
}

// static void addition_worker(int row, int columns, const Matrix &first, const Matrix &second, Matrix &result){

// }

void Matrix::addition_worker(int row, int columns, const Matrix &first, const Matrix &second, Matrix &result){
    for (int j = 0; j < columns; j++) {
        result.data(row, j) = first.data(row, j) + second.data(row, j);
    }
}

Matrix Matrix::operator *(const  Matrix &other)const{

    if ( _columns != other._rows ) {
        throw "Illegal Argument Exception";
    }
    Matrix result(_rows, other._columns);
    std::vector<std::thread> threads;

    for (int i = 0; i < _rows; i++) {
        cerr << _rows << " " << _columns << " " << other._columns << ":before pushback\n";
        threads.push_back(std::thread(Matrix::multiplication_worker, i, _columns, other._columns, *this, other, std::ref(result)));

        // for (int j = 0; j < other._columns; j++) {
        //     for (int k = 0; k < _columns; k++) {
        //         result.data(i, j) += data(i, k) * other.data(k, j);
        //     }
        // }
    }
 
    for(auto& th:threads){
        cerr << th.native_handle()<< ":before before join\n";
        th.join();
        delete &th;
    }

    return result;
}

void Matrix::multiplication_worker(int row, int columns, int other_columns, const Matrix &first, const Matrix &second, Matrix &result){
    cerr << "thread started: " << row;
    // for (int j = 0; j< columns; j++){
        // for (int k = 0; k < other_columns; k++) {
        //         result.data(row, j) += first.data(row, k) * second.data(k, j);
        // }
        // // result.data(row, j) += first.data(row, k) * second.data(k, j);

        //result.data(row, j) = first.data(row, j) + second.data(row, j);
    // }
}


void Matrix::print() const {

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            cout << data(i, j) << " ";
        }
        cout << endl;
    }
}