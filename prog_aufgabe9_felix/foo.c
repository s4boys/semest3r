#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
const char *conf="WINDOWS";
#endif
#ifdef linux
#define _GNU_SOURCE
#include <dlfcn.h>
const char *conf="LINUX";
#endif



#ifdef _WIN32
__declspec(dllexport)
#endif
void foo(const char *msg) {
    printf("In foo, configuration %s, from %s\n", conf, msg);
}
