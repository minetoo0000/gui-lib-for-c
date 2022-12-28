/*
    [ ���̺귯�� ]
    Timer.h

    [ ���� ]
    pause, resum�� ������ Ÿ�̸� ���̺귯��.
*/

#pragma once
#include <time.h>

enum enum$class_Timer
{
    Timer_state_null,
    Timer_state_pause,
    Timer_state_run,
};

struct type$class_Timer$timer_t
{
    // Ÿ�̸� ����.
    enum enum$class_Timer state;
    // ���� �ð�.
    clock_t current_timer;
    // ���� ~ ����, ���� ~ Ÿ�̸� ������ ���� "����" �ð� ����.
    clock_t resum_time;
};



// �и��� ���� �ð� �Լ�.
clock_t method$Timer$clock_ms()
{
    return( clock() / ( CLOCKS_PER_SEC / (clock_t)1000 ) );
}

// Ÿ�̸� ������ �Լ�.
struct type$class_Timer$timer_t method$class_Timer$newTimer( const clock_t setup_timer, const clock_t use_custom_clock_time )
{
    return(
        (struct type$class_Timer$timer_t)
        {
            .state = Timer_state_pause,
            .current_timer = setup_timer,
            .resum_time = use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms(),
        }
    );
}

// Ÿ�̸� ���� �Լ�.
void method$class_Timer$resum( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_pause )
    {
        obj->state = Timer_state_run;
        obj->resum_time = use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms();
    }
}

// Ÿ�̸� ���� �Լ�.
void method$class_Timer$pause( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_run )
    {
        obj->state = Timer_state_pause;
        obj->current_timer -= ( (use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms()) - obj->resum_time );
    }
}

// Ÿ�̸� ���� �ð� ��ȯ �Լ�.
clock_t method$class_Timer$get_current_timer( const struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_run )
    {
        return( obj->current_timer - ( (use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms()) - obj->resum_time ) );
    }
    else if ( obj->state == Timer_state_pause )
    {
        return( obj->current_timer );
    }
    else
    {
        return( 0 );
    }
}

// Ÿ�̸� �ð� ����.
void method$class_Timer$set_timer( struct type$class_Timer$timer_t* const obj, const clock_t setup_timer, const clock_t use_custom_clock_time )
{
    *obj = method$class_Timer$newTimer(setup_timer, use_custom_clock_time);
}



// Timer Ŭ���� ��ü.
struct class$Timer
{
    clock_t(*const clock_ms)(void);
    struct type$class_Timer$timer_t(*const newTimer)( const clock_t setup_timer, const clock_t use_custom_clock_time );
    void(*const resum)( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
    void(*const pause)( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
    clock_t(*const get_current_timer)( const struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
    void(*const set_timer)( struct type$class_Timer$timer_t* const obj, const clock_t setup_timer, const clock_t use_custom_clock_time );
} Timer = {
    .clock_ms = method$Timer$clock_ms,
    .newTimer = method$class_Timer$newTimer,
    .resum = method$class_Timer$resum,
    .pause = method$class_Timer$pause,
    .get_current_timer = method$class_Timer$get_current_timer,
    .set_timer = method$class_Timer$set_timer,
};
