#include <stdio.h>
#include <stdlib.h>

const char* module = "shared";

extern void foo(const char *msg);

__attribute__((constructor)) void init() {
    foo("shared");
}