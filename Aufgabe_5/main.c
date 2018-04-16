/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Peter Heusch
 *
 * Created on 3. April 2018, 11:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define  SIGN(x) (x>>31);
#define  MANT(x) (x&0x7FFFFF);
#define  EXPO(x) ((x>>23)&0xFF);
#define SPLIT(x, s, m, e) do {    \
  s = SIGN(x);                    \
  m = MANT(x);                    \
  e = EXPO(x);                    \
  if ( e != 0x00 && e != 0xFF ) { \
    m |= 0x800000;                \
  }                               \
} while ( 0 )                     
#define BUILD(x, s, m, e) do {               \
    x = (s << 31) | (e<<23) | (m&0x7FFFFF);  \
} while ( 0 )                                \


float foo(float *a, float *b) {
    uint32_t ia = *(unsigned int *) a;
    uint32_t ib = *(unsigned int *) b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;
    SPLIT(ia, signa, manta, expoa);
    SPLIT(ib, signb, mantb, expob);
    // Berechnen Sie hier signr mantr und expor!
    if ((signa == 0) & (manta == 0) & (expoa == 0)) { // Prüfung ob erste Zahl 0 ist
        signr = signb;
        mantr = mantb;
        expor = expob;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((signb == 0) & (mantb == 0) & (expob == 0)) { //Prüfung ob zweite Zahl 0 ist
        signr = signa;
        mantr = manta;
        expor = expoa;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    //Verschiebung(anpassung der Exponenten)
    int shifta = expoa - 127;
    int shiftb = expob - 127;
    if (shifta > 0) {
        manta = manta << shifta;
    } else {
        manta = manta >> shifta * (-1);
    }
    if (shiftb > 0) {
        mantb = mantb << shiftb;
    } else {
        mantb = mantb >> shiftb * (-1);
    }

    uint32_t ergebnis = 0;
    signr = 0;
    if (signa == 0 && signb == 0) { //Addition zweier positiven Zahlen
        ergebnis = manta + mantb;
    }
    if (signa == 0 && signb == 1) { //Addition positiver mit negativer zahl (a + (-b))
        if (mantb > manta) {
            signr = 1;
            ergebnis = mantb - manta;
        } else {
            ergebnis = manta - mantb;
        }
    }
    if (signa == 1 && signb == 0) { //Addition positiver mit negativer zahl ((-a) + b)
        if (manta > mantb) {
            signr = 1;
            ergebnis = manta - mantb;
        } else {
            ergebnis = mantb - manta;
        }
    }
    if (signa == 1 && signb == 1) {//Addition zweier negativen Zahlen ((-a) + (-b))
        signr = 1;
        ergebnis = manta + mantb;

    }


    int i = 31;
    while ((ergebnis >> i) == 0) { //"Rückverschiebung" ermitteln
        i--;
    }
    i++;
    i -= 24;

    expor = (127 + i);
    if (i < 0) { //Unterscheidung zwischen links und rechts verschiebung.
        mantr = (ergebnis << i * (-1));
    } else {
        mantr = (ergebnis >> i);
    }
    BUILD(result, signr, mantr, expor);
    return *(float *) &result;
}

float mal(float *a, float *b) {
    uint32_t ia = *(unsigned int *) a;
    uint32_t ib = *(unsigned int *) b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;
    SPLIT(ia, signa, manta, expoa);
    SPLIT(ib, signb, mantb, expob);

    signr = signa ^ signb;
    mantr = manta * mantb;
    expor = (expoa + expob) ;
//    int i = 31;
//    while ((mantr >> i) == 0) { //"Rückverschiebung" ermitteln
//        i--;
//    }
//    i++;
//    i -= 24;
//
//    expor = (127 + i);
//    if (i < 0) { //Unterscheidung zwischen links und rechts verschiebung.
//        (mantr << i * (-1));
//    } else {
//        (mantr >> i);
//    }
    BUILD(result, signr, mantr, expor);
    return *(float *) &result;
}

/*
 * 
 */

int main(int argc, char** argv) {
    // Nebenbedingungen im Test: 
    // Die Eingaben sind Zahlen im Bereich [-10.0...10.0]
    // Bei der Division kommt die 0 als Divisor nicht vor!
    //    float f = 1.5;
    //    float g = -2.4;
    //    float h = foo(&f, &g);
    float f = 3.9;
    float g = 5.4;
//        float h = mal(&f, &g);
    float i = foo(&f, &g);
    printf("%lf %lf  %lf", f, g, i);
    return (EXIT_SUCCESS);
}

