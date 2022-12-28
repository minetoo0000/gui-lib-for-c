#include <stdio.h>
#include "KeyboardInterface.h"
#include "../KeyboardInput/KeyboardInput.h"

typedef struct type$KeyboardInterface$pos_t pos_t;
typedef struct type$KeyboardInterface$Layer$select_obj_t select_obj_t;
typedef struct type$KeyboardInterface$Layer$layer_obj_t layer_obj_t;
typedef struct type$KeyboardInterface$Layer$layer_direction_obj_t layer_direction_obj_t;

int main()
{
    const struct class$KeyboardInterface Kbi = KeyboardInterface;
    Kbi.Layer.new_select_obj_init();

    while ( 1 )
    {
        
        
        
    }


    getchar();
    return( 0 );
}
