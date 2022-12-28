
#include <time.h>
#include <stdint.h>
#include <conio.h>
#include "../Timer/Timer.h"

#define UNICODE_16


typedef struct type$class_Keyboard$key_code_t
{
    // �ɼ�.
    uint8_t option;
    // Ű ��.
    #ifdef UNICODE_16
    uint16_t key_code;
    #else
    uint8_t key_code;
    #endif
} key_code_t;


int method$KeyboardInput$_getcharcode()
{
    #ifdef UNICODE_16
    return( _getch());
    #else
    return( _getwch());
    #endif
}


static key_code_t method$class_user_Keyboard$getCode(void)
{
    if ( _kbhit() ){
        // 1. Ű�� ���� ����.
        key_code_t set = {
            .option = 0,
            .key_code = 0,
        };

        // 2. Ű �ɼ� ����.
        if ( (set.key_code = method$KeyboardInput$_getcharcode()) == 224 )
        {
            set = (key_code_t){
                .option = set.key_code,
                .key_code = method$KeyboardInput$_getcharcode(),
            };
        }
        else if ( set.key_code == 0 )
        {
            set = (key_code_t){
                // .option = set.key_code,
                .option = 1,
                .key_code = method$KeyboardInput$_getcharcode(),
            };
        }
        return(set);
    }
    
    return(
        (key_code_t)
        {
            .option = 0,
            .key_code = 0,
        }
    );
}
// ���⿡�� Ű���� ���� �Լ����� �ۼ��� �Űŵ�.Ȥ�� ��������? ��....
// ���ڷ� ���� Ű���� �Է� ���� ������� ���� ����. ���� ���� �ִ� �Լ��� �����ص� �ǰ� �ƴϸ� ���� ���� ��.
// ����� ���Ѵ�� !
// 

static key_code_t method$class_user_Keyboard$flexible_getCode( key_code_t key_code )
{
    // 0. ����.
    // static uint8_t key_bf = 0;
    static key_code_t set_bf = {
        .option = 0,
        .key_code = 0,
    };
    static clock_t timer = 0;
    static uint8_t timer_mode = 0;  // 0 : ó�� �Է� Ÿ�̸�, 1 : ���� �Է� Ÿ�̸�.
    clock_t current_time = 0;
    current_time = Timer.clock_ms();

    // 1. Ű �Է��� ���� ��.
    if ( key_code.key_code != 0 )
    {
        // 1. ó���� �� 0.4�ʵ��� ������ Ű���� �����ȴ�.
        // - 0.4�� Ÿ�̸� ����.
        if ( current_time > timer )
        {
            // printf("\n Ÿ�̸� �ʱ�ȭ.\n");
            // 1. Ÿ�̸� ����.
            // - ó���� 0.4��, ���� �Է��� ��쿣 0.15�� Ÿ�̸� ����.
            // timer = current_time + ( timer_mode==0 ? 400 : 150 );
            clock_t regist = 0;
            if ( timer_mode == 0 )
            {
                regist = 500;
                // 1. Ÿ�̸Ӹ� ��� ������ ���Ŀ� ª�� Ÿ�̸� ���� ��ȯ.
                timer_mode = 1;
            }
            else
            {
                regist = 150;
            }
            timer = current_time + regist;

            // timer = current_time + o_Function(
            //     clock_t,
            //     Ktv01,

            //     clock_t return_timer = 0;
            //     if ( timer_mode == 0 )
            //     {
            //         // printf("\n 0.4�� ������.\n");
            //         return_timer = 500;
            //         // 1. Ÿ�̸Ӹ� ��� ������ ���Ŀ� ª�� Ÿ�̸� ���� ��ȯ.
            //         timer_mode = 1;
            //     }
            //     else
            //     {
            //         // printf("\n 0.15�� ������.\n");
            //         return_timer = 150;
            //     }
            //     Freturn(Ktv01, return_timer);
            // );

            // 2. Ű���� ������Ʈ �� ��ȯ.
            // key_bf = _getch();
            // if ( (set_bf.key_code = _getch()) == 224 )
            if ( key_code.option == 224 )
            {
                // set_bf = (key_code_t){
                //     .option = set_bf.key_code,
                //     .key_code = _getch(),
                // };
                set_bf.option = 224;
            }
            // else set_bf.option = 0;
            else
            {
                set_bf.option = 0;
            }
            set_bf.key_code = key_code.key_code;

            // printf("\n kye_bf ������Ʈ : %d\n", key_bf);
            // getchar();
            return( set_bf );
        }

        // 2. Ÿ�̸Ӱ� �Ϸ���� �ʾҴٸ� Ű���۸� ��ȯ.
        else
        {
            return( set_bf );
        }
    }

    // 2. Ű�� ������ �ʴ� ������ ��� ������ Ÿ�̸� ���� Ű���۸� ��ȯ.
    else if ( current_time <= timer )
    {
        return( set_bf );
    }

    // 3. ��� Ÿ�̸Ӱ� �Ϸ�Ǿ��ְ�, �ٽ� ó������ Ű�� �����ؾ��� ��.
    else
    {
        timer_mode = 0;
        return(
            (key_code_t)
            {
                .option = 0,
                .key_code = 0,
            }
        );
    }
}

static uint8_t method$class_Keyboard$checkBuffer()
{
    return( _kbhit() );
}
