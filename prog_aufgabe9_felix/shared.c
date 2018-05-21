#include <stdlib.h>
#include <stdio.h>

extern void foo(const char* c);

__attribute__((constructor))
void init() 
{
	char* module = "shared.c";
	foo(module);

}
