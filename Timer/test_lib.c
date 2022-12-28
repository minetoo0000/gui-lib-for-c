#include <stdio.h>
#include <stdint.h>
#include <conio.h>

// Timer.h �ҷ�����.
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


            
            // Ű���� ó��.
            if ( _kbhit() )
            {
                register const uint8_t code = _getch();

                // ���, �Ͻ�����.
                if ( code == 'p' )
                {
                    is_control = 1;
                    state = Timer_state_pause;
                }
                // ���, �̾ ����.
                else if ( code == 'r' )
                {
                    is_control = 1;
                    state = Timer_state_run;
                }
                // Ÿ�̸� ����.
                else if ( code == 'u' )
                {
                    is_control = 1;
                    // Timer.set_timer(&timer, 20000, current_time);
                    set_timer_from_input(&timer, &current_time);
                }
            }

            // Ű���� ��� ���� ó��.
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

            // Ÿ�̸� �Ϸ� ó��.
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