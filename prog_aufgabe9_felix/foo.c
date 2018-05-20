
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
const char *conf ="WINDOWS";
#else
const char *conf ="LINUX";
#endif

void foo(const char *msg) {
	printf("In foo, configuration %s, module %s, from %s \n", conf, "bananas", msg);
}