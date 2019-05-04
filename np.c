#include "types.h"
#include "user.h"

int
main(int argc, char** argv)
{
    char* np;
    
    #pragma GCC diagnostic ignored "-Wuninitialized"
    *np = 'c';
    printf(1, "%s\n", *np);
    exit();
}

