
#include <stdio.h>
#include <stdlib.h>

const char *conf;
#ifdef _WIN32
conf ="WINDOWS";
#else
conf ="LINUX";
#endif

void foo(const char *msg) {
	printf("In foo, configuration %s, module %s, from %s, conf, msg);
}

