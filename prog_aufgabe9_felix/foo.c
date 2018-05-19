#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
const char *conf="WINDOWS";
#elif defined linux
#define _GNU_SOURCE
#include <dlfcn.h>
const char *conf="LINUX";
#else
#error unknown configuration
#endif 

#if defined(WINDOWS)
__declspec(dllexport)
#endif
void foo(const char *msg) {
    printf("In foo, configuration %s, from %s\n", conf, msg);
}
