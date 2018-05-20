#include <stdio.h>
//#include "foo.c"
/*
#ifdef _WIN32
#include "shared.dll"
#else
#include "shared.so"
#endif
*/
extern void foo(const char* msg);

const char* module= "main.c";


int main(int argc, char** argv) {
    foo(module);
    return(0);
}

