#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

char* module= "shared.c";

__attribute__((constructor))
void init() 
{
    void *handle;
    int (*function)(char*);
    handle = dlopen(NULL,RTLD_LAZY);
    function = dlsym(handle,"foo");
    (*function)(module);
    dlclose(handle);
}
