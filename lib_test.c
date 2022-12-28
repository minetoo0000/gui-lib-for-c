#include <stdio.h>
#include "GUI-lib.h"

int main()
{
    while ( 1 )
    {
        if ( Keyboard.checkBuffer() )
        {
            key_code_t code = Keyboard.getCode();
            printf("\n option : %d key_code : %d\n", code.option, code.key_code);
        }
    }
    
    
    return( 0 );
}