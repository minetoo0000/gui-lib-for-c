#include "DebugSys.h"
#include <stdio.h>


int main()
{
    struct class$DebugSys debug = DebugSys;
    debug.library.init(0);

    debug.error("�ƴϾƴ� ������ �߻��ߴٱ�");

    printf("\n log_type : %d\n", debug.get_log(0).log_type);
    printf("\n log : %s\n", debug.get_log(0).log);


    getchar();
    return( 0 );
}