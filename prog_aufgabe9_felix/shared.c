
#include "foo.c"
extern void foo(const char* msg);

const char* module= "shared.c";

__attribute__((constructor))
void init() 
{
    foo(module);
}
