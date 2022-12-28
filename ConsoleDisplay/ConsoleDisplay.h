/*
    [라이브러리]
    ConsoleDisplay.h

    [설명]
    콘솔용(ansi escape 지원 필요) 간단한 디스플레이 라이브러리.
*/
// #pragma once

#include <stdint.h>
#include "../DebugSys/DebugSys.h"

// todo : ansi escape를 적용시킬 것임.
/*
    하지만 하나의 픽셀을 표현하는 데이터가 일정하지 않게 되므로 기존 방식을 사용할 수는 없다.
    유니코드도 지원하고 ansi escape를 사용할거라 그려질 버퍼의 크기는 항상 같지는 않다.
    현재 생각중인 방법은 삼중 버퍼링이다. 기존의 방법은 이중 버퍼링이였는데, 이번 개편은 버퍼의 크기가 일정하지 않으니
    모든 그리기 입력을 받은 후에 그 정보를 토대로 버퍼를 그리고 출력하도록 할 것이다.
    1. 픽셀 그리기 정보 버퍼에 그리기 정보를 모두 그린다.
    2. 픽셀 그리기 정보 버퍼를 토대로 디스플레이 버퍼에 그린다.
    3. 디스플레이 버퍼를 콘솔로 출력시킨다.
*/

#define CD_DEFAULT_CONSOLE_BUFFER_LANGE 30

// 색상 정보 순열.
enum enum$ConsoleDisplay$txt_style_t
{
    CD_style_default = 0,
    CD_color_black = 30,
    CD_color_red,
    CD_color_green,
    CD_color_yellow,
    CD_color_blue,
    CD_color_magenta,
    CD_color_cyan,
    CD_color_gray,
    CD_color_dark_gray = 90,
    CD_color_bright_red,
    CD_color_bright_green,
    CD_color_bright_yellow,
    CD_color_bright_blue,
    CD_color_bright_magenta,
    CD_color_bright_cyan,
    CD_color_white,
};

// 픽셀 정보 오브젝트.
struct type$ConsoleDisplay$pixel_obj_t
{
    uint8_t is_set_style:1;
    uint8_t is_rgb_color:1;
    uint8_t is_rgb_background_color:1;
    union _Color
    {
        enum enum$ConsoleDisplay$txt_style_t tag;
        struct _Rgb
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        } Rgb;
    } Color;
    union _BackgroundColor
    {
        enum enum$ConsoleDisplay$txt_style_t tag;
        struct _Rgb Rgb;
    } BackgroundColor;
    // enum enum$ConsoleDisplay$txt_style_t txt_style_tag;
    const uint8_t* ansi_escape;
    uint8_t ch;
};

// 그리기 버퍼 오브젝트.
struct type$ConsoleDisplay$canvas_buffer_t
{
    struct type$ConsoleDisplay$pixel_obj_t* const buffer;
    const uint16_t width;
    const uint16_t height;
};

// 디스플레이 버퍼 오브젝트.
struct type$ConsoleDisplay$display_buffer_t
{
    uint8_t* const buffer;
    const uint16_t width;
    const uint16_t height;
};



// 캔버스 버퍼 //
// 캔버스 버퍼 생성자.
const struct type$ConsoleDisplay$canvas_buffer_t method$ConsoleDisplay$Buffer$new_canvas(
    const uint16_t width,
    const uint16_t height
)
{
    // 1. 값 유효 확인.
    if ( width <= 0 || height <= 0 )
    {
        // 1. 에러 로그.
        DebugSys.error((uint8_t*const)DEBUGSYS_LOG_FORM("매개변수 width 또는 height가 0 이하이므로 함수 목적을 달성하지 못했습니다. 이러한 시도는 치명적일 수 있습니다."));
        // 2. 함수 종료.
        return(
            (struct type$ConsoleDisplay$canvas_buffer_t)
            {
                .buffer = 0,
                .width = 0,
                .height = 0,
            }
        );
    }

    // 1. 버퍼 메모리 할당.
    struct type$ConsoleDisplay$pixel_obj_t* const buffer = (struct type$ConsoleDisplay$pixel_obj_t*)malloc(sizeof(struct type$ConsoleDisplay$pixel_obj_t) * width * height);
    // 2. 버퍼 공백으로 초기화.
    for ( uint64_t index=0; index<width*height; index++ )
    {
        buffer[index] = (struct type$ConsoleDisplay$pixel_obj_t){
            .is_set_style = 0,
            .is_rgb_color = 0,
            .is_rgb_background_color = 0,
            .Color = {
                .tag = CD_style_default,
            },
            .BackgroundColor = {
                .tag = CD_style_default,
            },
            .ch = ' ',
            .ansi_escape = 0,
        };
    }
    // 3. 반환.
    return(
        (struct type$ConsoleDisplay$canvas_buffer_t)
        {
            .buffer = buffer,
            .width = width,
            .height = height,
        }
    );
}



// 디스플레이 버퍼 //
// 디스플레이 버퍼 전부 채우기 함수.
// - 캔버스 버퍼에 그리는 작업이 상위에 있으므로 출력(디스플레이) 버퍼에 그리는 작업은 캔버스 버퍼에 그리는 작업과 혼합될 수 없음.
// - 본 함수는 적절한 상황에서만 사용하도록 하고, 전체 화면을 채우는데 주로 사용한다.
uint8_t method$ConsoleDisplay$Buffer$draw_fill(
    struct type$ConsoleDisplay$display_buffer_t const display,
    const uint8_t* const wch
)
{
    // 1. 버퍼 유효 확인.
    if ( !display.buffer )
    {
        // 1. 에러 로그.
        DebugSys.error(DEBUGSYS_LOG_FORM("buffer 변수는 유효하지 않으므로 함수 목적을 달성하지 못했습니다. 이러한 시도는 치명적일 수 있습니다."));
        // 2. 함수 종료.
        return( 0 );
    }

    // 2. 버퍼에 그리기.
    uint64_t len = display.width * display.height;
    for ( uint64_t index=0; index<len; index++ )
    {
        if ( index % display.width == 0 ) display.buffer[index] = '\n';
        else display.buffer[index] = wch;
    }
}

// 디스플레이 버퍼 생성자.
struct type$ConsoleDisplay$display_buffer_t method$ConsoleDisplay$Buffer$new_display(
    uint16_t width,
    uint16_t height
)
{
    // 1. 갑 유효 확인.
    if ( !width || !height )  // 값이 0인 경우.
    {
        // 1. 에러 로그.
        DebugSys.error(DEBUGSYS_LOG_FORM("width 또는 height는 0이므로 함수 목적을 달성하지 못했습니다. 이러한 시도는 치명적일 수 있습니다."));
        // 2. 함수 종료.
        return(
            (struct type$ConsoleDisplay$display_buffer_t)
            {
                .buffer = 0,
                .width = 0,
                .height = 0,
            }
        );
    }

    // 2. 버퍼 메모리 할당.
    uint8_t* const buffer = malloc(width * height * CD_DEFAULT_CONSOLE_BUFFER_LANGE);
    // 3. 버퍼 공백으로 초기화.
    method$ConsoleDisplay$Buffer$draw_fill(
        (struct type$ConsoleDisplay$display_buffer_t){
            .buffer = buffer,
            .width = width,
            .height = height,
        },
        ' '
    );
    // 4. 디스플레이 반환.
    return(
        (struct type$ConsoleDisplay$display_buffer_t)
        {
            .buffer  = buffer,
            .width = width,
            .height = height,
        }
    );
}


// 픽셀 정보 버퍼 전부 채우기.
uint8_t method$ConsoleDisplay$draw$fill(
    struct type$ConsoleDisplay$canvas_buffer_t* const display,
    const uint8_t ch,
    const uint8_t* const ansi_escape
)
{
    // 1. 버퍼 유효성 확인.
    if ( !display || !display->buffer )
    {
        // 1. 에러 로그.
        DebugSys.error(DEBUGSYS_LOG_FORM("픽셀 정보 버퍼는 유효하지 않으므로 함수 목적을 달성하지 못했습니다"));
        // 2. 함수 종료.
        return( 0 );
    }

    // 2. 버퍼 채우기.
    uint64_t length = display->width * display->height;
    for ( uint64_t index=0; index<length; ++index )
    {
        display->buffer[index] = (struct type$ConsoleDisplay$pixel_obj_t){
            .is_set_style = 1,
            .is_rgb_color = 0,
            .is_rgb_background_color = 0,
            .Color = {
                .tag = CD_style_default,
            },
            .BackgroundColor = {
                .tag = CD_style_default,
            },
            .ch = ch,
            .ansi_escape = ansi_escape,
        };
    }
}
