#include <stdlib.h>
#include <stdio.h>
//#include <dlfcn.h>

//const char* module= "shared.c";

extern void foo(const char* c);

__attribute__((constructor))
void init() 
{
	char* module = "shared.c";
	foo(module);
    /*void *handle;
    int (*function)(char*);
    handle = dlopen(NULL,RTLD_LAZY);
    function = dlsym(handle,"foo");
    (*function)(module);
    dlclose(handle);*/
}
