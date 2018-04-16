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


int isZero(int manta, int signa, int expa){
    return (manta==0) & (signa==0) & (expa==0);
}


float foo(float *a, float *b) 
{
    uint32_t ia = *(unsigned int *)a;
    uint32_t ib = *(unsigned int *)b;
    uint32_t result = 0;
    int signa, signb, signr;
    int manta, mantb, mantr;
    int expoa, expob, expor;

    SPLIT(ia, signa, manta, expoa);
    SPLIT(ib, signb, mantb, expob);
    // Berechnen Sie hier signr mantr und expor!
    if(isZero(manta, signa, expoa)){
        signr = 0;
        mantr = 0;
        expor = 0;
    }
    else{

        signr = signa^signb;
        mantr = (manta * pow(2,23)) / mantb;
        expor = (expoa - expob +127);

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
    float f = -15;
    float g = -3.0;
    float h = foo(&f, &g);
    printf("%lf %lf %lf", f, g, h);
    return (EXIT_SUCCESS);
}
