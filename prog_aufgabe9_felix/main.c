#include <stdio.h>


extern void foo(const char* msg);

const char* module= "main.c";


int main(int argc, char** argv) {
    foo(module);
    return(0);
}

