/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: 71scfe1bif, 71hida1bif
 *
 * Created on 3. April 2018, 11:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

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
    if ((signa == 0) & (manta == 0) & (expoa == 0)) { // Prüfen ob a == 0
        signr = signb;
        mantr = mantb;
        expor = expob;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((signb == 0) & (mantb == 0) & (expob == 0)) { //Prüfen ob b == 0
        signr = signa;
        mantr = manta;
        expor = expoa;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    //Verschiebung(anpassung der Exponenten)
    int shifta = expoa - 127; 
    int shiftb = expob - 127;
    manta = manta << shifta;
    mantb = mantb << shiftb;
    signr = 0;
    if (signa == 0 && signb == 0) { //positive Zahlen
        mantr = manta + mantb;
    }
    if (signa == 0 && signb == 1) { //positive mit negativer Zahl 
        if (mantb > manta) {
            signr = 1;
            mantr = mantb - manta;
        } else {
            mantr = manta - mantb;
        }
    }
    if (signa == 1 && signb == 0) { //negative mit positiver Zahl 
        if (manta > mantb) {
            signr = 1;
            mantr = manta - mantb;
        } else {
            mantr = mantb - manta;
        }
    }
    if (signa == 1 && signb == 1) {//zwei negative Zahlen
        signr = 1;
        mantr = manta + mantb;

    }
    expor = 127;

    while (mantr > 0xFFFFFF) {   //Falls Mantisse größer als 0xFFFFFF muss sie normalisiert werden (Rightshift)
        mantr = mantr >> 1;
        expor ++;
    }
   
    while ((mantr) < 0x800000) { //Falls Mantisse kleiner als 0x800000 muss sie normalisiert werden (Leftshift)
        expor --;
        mantr = mantr << 1;
    }
    BUILD(result, signr, mantr, expor);
    return *(float *) &result;
}

float mal(float *a, float *b) 
{
    uint32_t ia = *(unsigned int *)a;
    uint32_t ib = *(unsigned int *)b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;
    SPLIT(ia, signa, manta, expoa);
    SPLIT(ib, signb, mantb, expob);

    if((expoa == 0 && manta == 0 ) || (expob == 0 && mantb == 0)) { //Wenn manta oder mantb 0 dann wird direkt 0 zurückgegeben
        return 0;
    }
    signr = signa ^ signb; //XOR Verknüpfung zur Bestimmung des Vorzeichens
    
    mantr = ((manta)/pow(2,23) * (mantb)); //Multiplikation der mantissen mit Anpassung an Bereich 
   
    expor = (expoa + expob) - 127;  //Exponentenaddition
    while (mantr > 0xFFFFFF) {      //wie bei Addition (Normalisierung)
        mantr = mantr >> 1;
        expor ++;
    }
   
    while ((mantr) < 0x800000) {
        expor --;
        mantr = mantr << 1;
    }
    BUILD(result, signr, mantr, expor);
    return *(float *)&result;
}

/*
 * 
 */

int main(int argc, char** argv) {
    // Nebenbedingungen im Test: 
    // Die Eingaben sind Zahlen im Bereich [-10.0...10.0]
    // Bei der Division kommt die 0 als Divisor nicht vor!
    float f = -3.6;
    float g = 9.424774;
    float h = foo(&f, &g);
    float i = 3.578126;
    float j = 2.34523;
    float k = mal(&i, &j);
    printf("Add: %lf %lf %lf\n", f, g, h);
    printf("Mal: %lf %lf %lf", i, j, k);
    
    return (EXIT_SUCCESS);
}

