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

#define  SIGN(x) (x>>31); // rightshift von x um 31 stellen, sign bleibt übrig
#define  MANT(x) (x&0x7FFFFF); // Logisches UND mit 23 1en (7FFFFF)
#define  EXPO(x) ((x>>23)&0xFF); // rightshift, mant wird abgeschnitten, & 8 1en -> schneidet s ab
#define SPLIT(x, s, m, e) do {    \
  s = SIGN(x);                    \
  m = MANT(x);                    \
  e = EXPO(x);                    \
  if ( e != 0x00 && e != 0xFF ) { \
    m |= 0x800000;                \
  }                               \
} while ( 0 )  
//100000000000000000000000 24 Zeichen = 0x800000
// wenn exponent nicht 0 und 255 ist
// --> hier wird 1 vor dem komma hinzugefügt sehr wichtig
#define BUILD(x, s, m, e) do {               \
    x = (s << 31) | (e<<23) | (m&0x7FFFFF);  \
} while ( 0 )                                \
//baut neue fließkommazahl

float substract(float *a, float *b) {
    uint32_t ia = *(unsigned int *) a; // 1069547520 = 00111111110000000000000000000000
    uint32_t ib = *(unsigned int *) b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;
    SPLIT(ia, signa, manta, expoa); //manta 110000000000000000000000 24 bit 1,1 passt
    SPLIT(ib, signb, mantb, expob); //mantb 100110011001100110011010 24 bit
    // Berechnen Sie hier signr mantr und expor!
    signr = 0;
    if ((signa == signb) & (manta == mantb) & (expoa == expob)) { // falls A = B
        signr = 0;
        mantr = 0;
        expor = 0;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((manta == 0) & (expoa == 0)) { // falls Operant A = 0
        if (signb == 0){
            signr = 1;
        }
        mantr = mantb;
        expor = expob;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((signb == 0) & (mantb == 0) & (expob == 0)) { // falls Operant B = 0
        signr = signa;
        mantr = manta;
        expor = expoa;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    int aShift = expoa - 127;
    int bShift = expob - 127;
    // verschiebe mantissen so dass sie * 2⁰ sind
    manta = shift(manta, (-1) * aShift); // 100000000000000000000000 wird zu 100000000000000000000000, logisch ist 1
    mantb = shift(mantb, (-1) * bShift); // 100000000000000000000000 wird zu 10000000000000000000000000, unlogisch
    uint32_t ergebnis = 0;

    //bestimme Vorzeichen des Ergebnisses
    
    if (signa == 0 && signb == 0) {
        if (mantb > manta) {
            signr = 1;
            ergebnis = mantb - manta;
        } else {
            ergebnis = manta - mantb;
        }
    }
    if (signa == 1 & signb == 1){
        if (mantb > manta){
            ergebnis = mantb - manta;
        }
        else {
            signr = 1;
            ergebnis = manta - mantb;
        }
    }
    if (signa == 0 & signb == 1) {
        ergebnis = mantb + manta;
    }
    if (signa == 1 & signb ==0){
        signr = 1;
        ergebnis = manta + mantb;
    }
    // suche stelle der ersten 1 im ergebnis
    int i = 31; // mantisse ist 11000000000000000000000
    while ((ergebnis >> i) == 0) {
        i--;
    }
    i++; // stelle der ersten 1 ist jetzt i
    i -= 24; // differenz zur zielstelle, 24 ist versteckte bit stelle
    // verschiebefaktor i steht fest
    expor = (127 + i);
    mantr = shift(ergebnis,i); // ergebnis wird auf 1, gestellt
//mantr sollte dann 110000000000000000000000 sein, 1,1 * 2-1
    BUILD(result, signr, mantr, expor);
    return *(float *) &result;
}
int shift(uint32_t mantisse, int shiftFactor){
    if (shiftFactor >= 0){
        return mantisse >> shiftFactor;
    }
    else {
        return mantisse << (-1)*shiftFactor;
    }
}

float add(float *a, float *b) {
    uint32_t ia = *(unsigned int *) a; // 1069547520 = 00111111110000000000000000000000
    uint32_t ib = *(unsigned int *) b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;
    SPLIT(ia, signa, manta, expoa); //manta 110000000000000000000000 24 bit 1,1 passt
    SPLIT(ib, signb, mantb, expob); //mantb 100110011001100110011010 24 bit
    // Berechnen Sie hier signr mantr und expor!
    if ((signa == 0) & (manta == 0) & (expoa == 0)) { // falls Operant A = 0
        signr = signb;
        mantr = mantb;
        expor = expob;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((signb == 0) & (mantb == 0) & (expob == 0)) { // falls Operant B = 0
        signr = signa;
        mantr = manta;
        expor = expoa;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }

    int aShift = expoa - 127;
    int bShift = expob - 127;
    // verschiebe mantissen so dass sie * 2⁰ sind
    manta = manta << aShift;
    mantb = mantb << bShift; // 1001100110011001100110100 eine Null länger, passt
    uint32_t ergebnis = 0;
    signr = 0;
    if (signa == 0 && signb == 0) {
        ergebnis = manta + mantb; // 1111100110011001100110100
    }
    if (signa == 0 && signb == 1) {
        if (mantb > manta) {
            signr = 1;
            ergebnis = mantb - manta;
        } else {
            ergebnis = manta - mantb;
        }

    }

    int i = 31;
    while ((ergebnis >> i) == 0) {
        i--; //i ist hier dann 24, bedeutet erste 1 an stelle 24 + 1 = 25, soll an 24 sein
    }
    i++; // stelle der ersten 1 ist jetzt i
    i -= 24; // differenz zur zielstelle, 24 ist versteckte bit stelle

    expor = (127 + i);
    mantr = (ergebnis >> i); //111110011001100110011010 eine Null weniger

    BUILD(result, signr, mantr, expor);
    return *(float *) &result;
}

float divide(float *a, float*b) {
    uint32_t ia = *(unsigned int *) a; // 1069547520 = 00111111110000000000000000000000
    uint32_t ib = *(unsigned int *) b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr; // a : 100000000000000000000000 -> 0|10000000|0 also passt
    int expoa, expob, expor; // b : _> 0|01111111|0 passt
    SPLIT(ia, signa, manta, expoa); //manta 110000000000000000000000 24 bit 1,1 passt
    SPLIT(ib, signb, mantb, expob); //mantb 100110011001100110011010 24 bit
    signr = 0;
    if ((signa ^ signb) == 1) {
        signr = 1;
    }
    //Rechnung
    if ((mantb == 0x800000) & (expob == 127)) { // falls Operant B = 1
        mantr = manta;
        expor = expoa;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    if ((expoa == expob) & (manta == mantb)) { // vielleicht unnötig, wenn a = b direkt 1
        expor = 127;
        mantr = 0x800000;
        BUILD(result, signr, mantr, expor);
        return *(float *) &result;
    }
    int aShift = expoa - 127;
    int bShift = expob - 127;
    // verschiebe mantissen so dass sie * 2⁰ sind
    uint32_t mantaBits = manta << aShift;
    uint32_t mantbBits = mantb << bShift;
    uint32_t ergebnis = 0;

    ergebnis = mantaBits / mantbBits; //dez in bin 10100000000000000000000000 / dez in bin 100000000000000000000000

    int i = 31;
    while ((ergebnis >> i) == 0) {
        i--; //i ist hier dann 24, bedeutet erste 1 an stelle 24 + 1 = 25, soll an 24 sein
    }
    i++; // stelle der ersten 1 ist jetzt i
    i -= 24; // differenz zur zielstelle, 24 ist versteckte bit stelle

    expor = (127 + i);
    mantr = (ergebnis >> i); //111110011001100110011010 eine Null weniger

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
    float f =-1;
    float g =-1;
//    float addF = add(&f, &g);
    float subF = substract(&f, &g);
//    float divF = divide(&f, &g);
//    printf("%lf + %lf = %lf\n", f, g, addF);
    printf("%lf - %lf = %lf\n", f, g, subF);
//    printf("%lf / %lf = %lf\n", f, g, divF);
    return (EXIT_SUCCESS);
}

