#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ConsoleDisplay.h"

int main()
{
    DebugSys.library.init(0);
    DebugSys.error(DEBUGSYS_LOG_FORM("�ƴϾƴϾƴϾƤ�����"));
    printf("\n %s\n", DebugSys.get_log(0).log);

 

    getchar();
    return( 0 );
}