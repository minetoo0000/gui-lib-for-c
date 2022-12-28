/*
    [���̺귯��]
    ConsoleDisplay.h

    [����]
    �ֿܼ�(ansi escape ���� �ʿ�) ������ ���÷��� ���̺귯��.
*/
// #pragma once

#include <stdint.h>
#include "../DebugSys/DebugSys.h"

// todo : ansi escape�� �����ų ����.
/*
    ������ �ϳ��� �ȼ��� ǥ���ϴ� �����Ͱ� �������� �ʰ� �ǹǷ� ���� ����� ����� ���� ����.
    �����ڵ嵵 �����ϰ� ansi escape�� ����ҰŶ� �׷��� ������ ũ��� �׻� ������ �ʴ�.
    ���� �������� ����� ���� ���۸��̴�. ������ ����� ���� ���۸��̿��µ�, �̹� ������ ������ ũ�Ⱑ �������� ������
    ��� �׸��� �Է��� ���� �Ŀ� �� ������ ���� ���۸� �׸��� ����ϵ��� �� ���̴�.
    1. �ȼ� �׸��� ���� ���ۿ� �׸��� ������ ��� �׸���.
    2. �ȼ� �׸��� ���� ���۸� ���� ���÷��� ���ۿ� �׸���.
    3. ���÷��� ���۸� �ַܼ� ��½�Ų��.
*/

#define CD_DEFAULT_CONSOLE_BUFFER_LANGE 30

// ���� ���� ����.
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

// �ȼ� ���� ������Ʈ.
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

// �׸��� ���� ������Ʈ.
struct type$ConsoleDisplay$canvas_buffer_t
{
    struct type$ConsoleDisplay$pixel_obj_t* const buffer;
    const uint16_t width;
    const uint16_t height;
};

// ���÷��� ���� ������Ʈ.
struct type$ConsoleDisplay$display_buffer_t
{
    uint8_t* const buffer;
    const uint16_t width;
    const uint16_t height;
};



// ĵ���� ���� //
// ĵ���� ���� ������.
const struct type$ConsoleDisplay$canvas_buffer_t method$ConsoleDisplay$Buffer$new_canvas(
    const uint16_t width,
    const uint16_t height
)
{
    // 1. �� ��ȿ Ȯ��.
    if ( width <= 0 || height <= 0 )
    {
        // 1. ���� �α�.
        DebugSys.error((uint8_t*const)DEBUGSYS_LOG_FORM("�Ű����� width �Ǵ� height�� 0 �����̹Ƿ� �Լ� ������ �޼����� ���߽��ϴ�. �̷��� �õ��� ġ������ �� �ֽ��ϴ�."));
        // 2. �Լ� ����.
        return(
            (struct type$ConsoleDisplay$canvas_buffer_t)
            {
                .buffer = 0,
                .width = 0,
                .height = 0,
            }
        );
    }

    // 1. ���� �޸� �Ҵ�.
    struct type$ConsoleDisplay$pixel_obj_t* const buffer = (struct type$ConsoleDisplay$pixel_obj_t*)malloc(sizeof(struct type$ConsoleDisplay$pixel_obj_t) * width * height);
    // 2. ���� �������� �ʱ�ȭ.
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
    // 3. ��ȯ.
    return(
        (struct type$ConsoleDisplay$canvas_buffer_t)
        {
            .buffer = buffer,
            .width = width,
            .height = height,
        }
    );
}



// ���÷��� ���� //
// ���÷��� ���� ���� ä��� �Լ�.
// - ĵ���� ���ۿ� �׸��� �۾��� ������ �����Ƿ� ���(���÷���) ���ۿ� �׸��� �۾��� ĵ���� ���ۿ� �׸��� �۾��� ȥ�յ� �� ����.
// - �� �Լ��� ������ ��Ȳ������ ����ϵ��� �ϰ�, ��ü ȭ���� ä��µ� �ַ� ����Ѵ�.
uint8_t method$ConsoleDisplay$Buffer$draw_fill(
    struct type$ConsoleDisplay$display_buffer_t const display,
    const uint8_t* const wch
)
{
    // 1. ���� ��ȿ Ȯ��.
    if ( !display.buffer )
    {
        // 1. ���� �α�.
        DebugSys.error(DEBUGSYS_LOG_FORM("buffer ������ ��ȿ���� �����Ƿ� �Լ� ������ �޼����� ���߽��ϴ�. �̷��� �õ��� ġ������ �� �ֽ��ϴ�."));
        // 2. �Լ� ����.
        return( 0 );
    }

    // 2. ���ۿ� �׸���.
    uint64_t len = display.width * display.height;
    for ( uint64_t index=0; index<len; index++ )
    {
        if ( index % display.width == 0 ) display.buffer[index] = '\n';
        else display.buffer[index] = wch;
    }
}

// ���÷��� ���� ������.
struct type$ConsoleDisplay$display_buffer_t method$ConsoleDisplay$Buffer$new_display(
    uint16_t width,
    uint16_t height
)
{
    // 1. �� ��ȿ Ȯ��.
    if ( !width || !height )  // ���� 0�� ���.
    {
        // 1. ���� �α�.
        DebugSys.error(DEBUGSYS_LOG_FORM("width �Ǵ� height�� 0�̹Ƿ� �Լ� ������ �޼����� ���߽��ϴ�. �̷��� �õ��� ġ������ �� �ֽ��ϴ�."));
        // 2. �Լ� ����.
        return(
            (struct type$ConsoleDisplay$display_buffer_t)
            {
                .buffer = 0,
                .width = 0,
                .height = 0,
            }
        );
    }

    // 2. ���� �޸� �Ҵ�.
    uint8_t* const buffer = malloc(width * height * CD_DEFAULT_CONSOLE_BUFFER_LANGE);
    // 3. ���� �������� �ʱ�ȭ.
    method$ConsoleDisplay$Buffer$draw_fill(
        (struct type$ConsoleDisplay$display_buffer_t){
            .buffer = buffer,
            .width = width,
            .height = height,
        },
        ' '
    );
    // 4. ���÷��� ��ȯ.
    return(
        (struct type$ConsoleDisplay$display_buffer_t)
        {
            .buffer  = buffer,
            .width = width,
            .height = height,
        }
    );
}


// �ȼ� ���� ���� ���� ä���.
uint8_t method$ConsoleDisplay$draw$fill(
    struct type$ConsoleDisplay$canvas_buffer_t* const display,
    const uint8_t ch,
    const uint8_t* const ansi_escape
)
{
    // 1. ���� ��ȿ�� Ȯ��.
    if ( !display || !display->buffer )
    {
        // 1. ���� �α�.
        DebugSys.error(DEBUGSYS_LOG_FORM("�ȼ� ���� ���۴� ��ȿ���� �����Ƿ� �Լ� ������ �޼����� ���߽��ϴ�"));
        // 2. �Լ� ����.
        return( 0 );
    }

    // 2. ���� ä���.
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
