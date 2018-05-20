#include <stdio.h>
#include <stdlib.h>

const char* module = "main";
extern void foo(const char *msg);

int main(int argc, char** argv){

    foo("main");
}



