#include <stdio.h>
#include "Etc.h"

int main()
{
    struct typeee
    {
        uint8_t a;
        uint8_t b;
    } ddd = {
        .a = 12,
        .b = 14,
    };
    
    uint64_t get = Etc.struct_to_8byte(0, ddd);
    printf("\n get : %lld\n", get);


    getchar();
    return( 0 );
}