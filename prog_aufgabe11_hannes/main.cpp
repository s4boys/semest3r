/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Peter Heusch
 *
 * Created on 31. Mai 2018, 19:32
 */

#include <cstdlib>
#include <iostream>
#include "Matrix.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Matrix m1(3,1);
    Matrix m2(1,4);
    m1.data(0, 0) = 1.0;
    m1.data(1, 0) = 2.0;
    m1.data(2, 0) = 3.0;
    m2.data(0, 0) = 1.0;
    m2.data(0, 1) = 2.0;
    m2.data(0, 2) = 3.0;
    m2.data(0, 3) = 4.0;
    Matrix m3 = m1 * m2;
    Matrix m4 = m1 + m1;
    cout << "m1" << endl;
    m1.print();
    cout << "m2" << endl;
    m2.print();
    cout << "m3" << endl;
    m3.print();
    cout << "m4" << endl;
    m4.print();
    return 0;
}

