/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Peter Heusch
 *
 * Created on 8. Mai 2018, 10:49
 */

#include <cstdlib>
#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include "Fraction.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 

{
    Fraction two = 2;
    Fraction three = 3;
    Fraction pie = 3.1415926;
    
    assert(two == Fraction(4,2));
    assert(pie == Fraction(22,7));
    assert((double)(three / two) == 1.5);
    return 0;
}

