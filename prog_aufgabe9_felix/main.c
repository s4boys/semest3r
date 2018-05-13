#include <stdio.h>
#include <stdlib.h>
#include <foo.c>
#include <shared.c>

const char* module = "main";
void foo(const char *msg);

int main(int argc, char** argv){
#ifdef WIN32
__declspec(dllexport) foo(module);
#else
foo(module);
#endif

}



