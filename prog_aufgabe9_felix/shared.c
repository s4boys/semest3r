#include <stdio.h>
#include <stdlib.h>
#include <foo.c>

const char* module = "shared";


void init(){
foo(module) __attribute__((constructor));

}
