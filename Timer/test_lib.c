#include <stdio.h>
#include <stdint.h>
#include <conio.h>

// Timer.h 불러오기.
#include "Timer.h"
typedef struct type$class_Timer$timer_t timer_t;

void set_timer_from_input( timer_t* const timer, clock_t* const use_custom_clock_time )
{
    clock_t set_timer = 0;
    printf("\n set timer : ");scanf("%ld", &set_timer);

    *use_custom_clock_time = Timer.clock_ms();
    Timer.set_timer(timer, set_timer, *use_custom_clock_time);
}


int main()
{
    #define delay 1
    enum enum$class_Timer state = Timer_state_pause;
    uint8_t is_control = 1;
    timer_t timer = Timer.newTimer(60000, 0);

    


    {
        while ( 1 )
        {
            clock_t current_time = Timer.clock_ms();


            
            // 키보드 처리.
            if ( _kbhit() )
            {
                register const uint8_t code = _getch();

                // 명령, 일시정지.
                if ( code == 'p' )
                {
                    is_control = 1;
                    state = Timer_state_pause;
                }
                // 명령, 이어서 시작.
                else if ( code == 'r' )
                {
                    is_control = 1;
                    state = Timer_state_run;
                }
                // 타이머 설정.
                else if ( code == 'u' )
                {
                    is_control = 1;
                    // Timer.set_timer(&timer, 20000, current_time);
                    set_timer_from_input(&timer, &current_time);
                }
            }

            // 키보드 명령 동작 처리.
            if ( is_control )
            {
                if ( state == Timer_state_run )
                {
                    Timer.resum(&timer, current_time);
                }
                else if ( state == Timer_state_pause )
                {
                    Timer.pause(&timer, current_time);
                }

                is_control = 0;
            }

            // 타이머 완료 처리.
            if ( Timer.get_current_timer(&timer, current_time) <= 0 )
            {
                is_control = 1;
                state = Timer_state_pause;
                printf("\n timer end!\n");
            }
            else
            {
                printf("\n current_timer : %ld\n", ~(Timer.get_current_timer(&timer, current_time)<<1));
            }
            
        }
    }

    getchar();
    return( 0 );
}