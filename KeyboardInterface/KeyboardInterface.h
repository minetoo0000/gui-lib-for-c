/*
    [????귯??]
    KeyboardInterface.h

    [????]
    GUI?? ???? ????? ???? ????????? ????귯??. ?????? ???α???? ???? ?????? ???? ?????.
    
    tab : ??? ????? ???? ?????? ????? 
*/

#pragma once
#include <stdint.h>
#include <conio.h>
#include <malloc.h>
#include "../KeyboardInput/KeyboardInput.h"
#include "../DebugSys/DebugSys.h"


#define DEFAULT_LAYER_DIRECTION_LENGTH 10

// ???.
struct type$KeyboardInterface$pos_t
{
    int32_t pos_x;
    int32_t pos_y;
};

// ???? ????? ????.
enum enum$KeyboardInterface$Layer$select_obj_type
{
    KBI_type_null,  // ????, ????.
    KBI_type_btn,  // ????, ???.
    KBI_type_window,  // ????, ?.
    KBI_type_scroll,  // ????, ?????.
    KBI_type_textbox,  // ????, ??????.
};

// ???? ??? ???????.
struct type$KeyboardInterface$Layer$select_obj_t
{
    uint16_t tab_index;
    struct type$KeyboardInterface$pos_t dot_1;
    struct type$KeyboardInterface$pos_t dot_2;
    enum enum$KeyboardInterface$Layer$select_obj_type type;
    uint8_t is_active;
};

typedef uint16_t type$KeyboardInterface$Layer$tab_index_t;
typedef uint16_t type$KeyboardInterface$Layer$layer_id_t;
// ????????? ????? ???? ???????.
struct type$KeyboardInterface$Layer$layer_obj_t
{
    type$KeyboardInterface$Layer$tab_index_t tab_length;
    type$KeyboardInterface$Layer$tab_index_t current_tab_index;
    ////////////////////////////////////////////////////////////////////////////// ???? ??? ?κ?!!!!!!!!
    struct type$KeyboardInterface$Layer$select_obj_t* select_objs;
    uint8_t is_update_only_this_window;
};

// ????????? ????? ?迭 ???????. (????? ???)
struct type$KeyboardInterface$Layer$layer_direction_obj_t
{
    uint16_t max_length;
    uint16_t current_direction;
    //////////////////////////////////////////////////////////////////// ???? ??? ?κ?!!!!!!!!!!!!!111
    struct type$KeyboardInterface$Layer$layer_obj_t* layer_objs;
};



// ?? ????? ????? ????? ???.
// type$KeyboardInterface$Layer$tab_index_t method$KeyboardInterface$Layer$layer_id_writer()
// {
//     static type$KeyboardInterface$Layer$layer_id_t layer_id_counter = 0;
//     return( ++layer_id_counter );
// }


// ?? ?ε??? //
static type$KeyboardInterface$Layer$tab_index_t val$KeyboardInterface$Tab$tab_index_counter = 0;
// ?? ?ε??? ????? ???? ???.
void method$KeyboardInterface$Tab$tab_index_writer_init()
{
    val$KeyboardInterface$Tab$tab_index_counter = 0;
}
// ?? ?ε??? ????? ???.
type$KeyboardInterface$Layer$tab_index_t method$KeyboardInterface$Tab$tab_index_writer()
{
    return( val$KeyboardInterface$Tab$tab_index_counter++ );
}


// ? ??? ???.
enum enum$KeyboardInterface$Key$interface_key
{
    KBI_click_null,  // null
    KBI_click_F1,  // F1
    KBI_click_F2,  // F2
    KBI_click_tab,  // tab.
    KBI_click_esc,  // esc
    KBI_click_arrow_top,  // ???h? ??.
    KBI_click_arrow_right,  // ???h? ??????.
    KBI_click_arrow_bottom,  // ???h? ???.
    KBI_click_arrow_left,  // ???h? ????.
    KBI_click_enter,  // ??? ok.
    KBI_click_backspace,  // backspace.
    KBI_click_delete,  // delete.
};
enum enum$KeyboardInterface$Key$interface_key method$KeyboardInterface$Key$get_key_state( const key_code_t key )
{    
    if ( key.option == 0 )
    {
        if ( key.key_code == 9 )
            return( KBI_click_tab );
        else if ( key.key_code == 13 )
            return( KBI_click_enter );
        else if ( key.key_code == 60 )
            return( KBI_click_F2 );
        else if ( key.key_code == 27 )
            return( KBI_click_esc );
        else if ( key.key_code == 8 )
            return( KBI_click_backspace );
    }
    else if ( key.option == 1 )
    {
        if ( key.key_code == 59 )
            return( KBI_click_F1 );
        else if ( key.key_code == 60 )
            return( KBI_click_F2 );
    }
    else if ( key.option == 224 )
    {
        if ( key.key_code == 72 )
            return( KBI_click_arrow_top );
        else if ( key.key_code == 77 )
            return( KBI_click_arrow_right );
        else if ( key.key_code == 80 )
            return( KBI_click_arrow_bottom );
        else if ( key.key_code == 75 )
            return( KBI_click_arrow_left );

        else if ( key.key_code == 83 )
            return( KBI_click_delete );
    }

    return( KBI_click_null );
}



// ????????? ??????? ????? ??? //
// ????????? ????? ??????? ????? ???.
uint8_t method$KeyboardInterface$Layer$check_layer_obj( const struct type$KeyboardInterface$Layer$layer_obj_t layer_obj  )
{
    if ( !layer_obj.select_objs ) return( 0 );  // ?????????? ??????? ????.
    else return( 1 );
}
// ????????? ????? ??? ??????? ????? ???.
uint8_t method$KeyboardInterface$Layer$check_layer_direction_obj( const struct type$KeyboardInterface$Layer$layer_direction_obj_t layer_direction_obj  )
{
    if ( !layer_direction_obj.layer_objs ) return( 0 );  // ?????????? ??????? ????.
    else return( 1 );
}



// ????????? ???? ??? ??????? //
// ????????? ???? ??? ??????? ?????? ??? ???? ???. (???? ????? ?? ?ε??? ????)
void method$KeyboardInterface$Layer$new_select_obj_init()
{
    method$KeyboardInterface$Tab$tab_index_writer_init();
}
// ????????? ???? ??? ??????? ?????? ???.
struct type$KeyboardInterface$Layer$select_obj_t method$KeyboardInterface$Layer$new_select_obj(
    const enum enum$KeyboardInterface$Layer$select_obj_type type,
    const struct type$KeyboardInterface$pos_t dot_1, const struct type$KeyboardInterface$pos_t dot_2,
    const uint8_t is_active
)
{
    return(
        (struct type$KeyboardInterface$Layer$select_obj_t)
        {
            .tab_index = method$KeyboardInterface$Tab$tab_index_writer(),
            .dot_1 = dot_1,
            .dot_2 = dot_2,
            .type = type,
            .is_active = is_active,
        }
    );
}



// ????????? ????? ???? ??????? //
// ????????? ????? ???? ??????? ??????.
struct type$KeyboardInterface$Layer$layer_obj_t method$KeyboardInterface$Layer$new_layer_obj(
    const type$KeyboardInterface$Layer$tab_index_t tab_length,
    const type$KeyboardInterface$Layer$tab_index_t start_tab,
    const uint8_t is_update_only_this_window
)
{
    return(
        (struct type$KeyboardInterface$Layer$layer_obj_t)
        {
            .tab_length = tab_length,
            .current_tab_index = start_tab,
            .is_update_only_this_window = is_update_only_this_window,
            .select_objs = malloc(
                sizeof(struct type$KeyboardInterface$Layer$select_obj_t) * tab_length
            ),
        }
    );
}
// ????????? ????? ???? ???? ??? ??????? ??? ???.
void method$KeyboardInterface$Layer$insert_select_obj_to_layer(
    struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
    const struct type$KeyboardInterface$Layer$select_obj_t select_obj
)
{
    struct type$KeyboardInterface$Layer$select_obj_t* new_space = realloc(
        layer_obj->select_objs,
        sizeof(struct type$KeyboardInterface$Layer$select_obj_t) * (++layer_obj->tab_length)
    );
    
    if ( new_space == 0 )
    {
        --layer_obj->tab_length;
        // DebugSys.error(DEBUGSYS_LOG_FORM("realloc?? ??????? ????? ??? ????? ??????? ????????."));
        DebugSys.error(DEBUGSYS_LOG_FORM("realloc 함수의 메모리 할당 작업은 실패했습니다. 개발자는 이에 대응하는 예외를 작성해야합니다."));
    }
    else
    {
        layer_obj->select_objs = new_space;
        layer_obj->select_objs[layer_obj->tab_length-1] = select_obj;
        // DebugSys.debug(DEBUGSYS_LOG_FORM("??翡 ??????????."));
        DebugSys.debug(DEBUGSYS_LOG_FORM("레이어 오브젝트에 선택 대상 오브젝트를 성공적으로 넣음."));
    }
}
// ????? ???? ??? ??????? ???? ???????? ???.
struct type$KeyboardInterface$Layer$select_obj_t method$KeyboardInterface$Layer$get_select_obj_of_layer(
    struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
    const type$KeyboardInterface$Layer$tab_index_t index
)
{
    return(
        (struct type$KeyboardInterface$Layer$select_obj_t)
        layer_obj->select_objs[index]
    );
}
// ????? ???? ??? ??????? ???? ???? ???.
void method$KeyboardInterface$Layer$edit_select_obj_of_layer(
    struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
    const type$KeyboardInterface$Layer$tab_index_t index,
    const struct type$KeyboardInterface$Layer$select_obj_t select_obj
)
{
    layer_obj->select_objs[index] = select_obj;
}
// ????? ????????? ???? ?ε???, ????????.
void method$KeyboardInterface$Layer$layer_obj_next_index(
    struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj
)
{
    // 0. ????? ??????? ??´?? ???? ?α?.
    if ( !method$KeyboardInterface$Layer$check_layer_obj(*layer_obj) )
    {
        // 1. ???? ?α?.
        // DebugSys.error(DEBUGSYS_LOG_FORM("????? ????????? ??????? ??? ??? ??? ?????? ??????? ????????. ????? ????? ??????? ?? ??????."));
        DebugSys.error(DEBUGSYS_LOG_FORM("레이어 오브젝트가 유효하지 않아 함수 목적을 달성하지 못했습니다. 이는 치명적인 시도일 수 있습니다."));
        // 2. ??? ????.
        return;
    }
    // 1. ??? ?? ?ε????? ???? ????? ???.
    if ( layer_obj->current_tab_index < layer_obj->tab_length-1 ) ++layer_obj->current_tab_index;
    // 2. ??븦 ??? ??? ??쿣 0?????? ????????.
    else layer_obj->current_tab_index = 0;
}
// ????? ????????? ???? ?ε???, ????????.
void method$KeyboardInterface$Layer$layer_obj_previous_index(
    struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj
)
{
    // 0. ????? ??????? ??´?? ???? ?α?.
    if ( !method$KeyboardInterface$Layer$check_layer_obj(*layer_obj) )
    {
        // 1. ???? ?α?.
        // DebugSys.error(DEBUGSYS_LOG_FORM("????? ????????? ??????? ??? ??? ??? ?????? ??????? ????????. ????? ????? ??????? ?? ??????."));
        DebugSys.error(DEBUGSYS_LOG_FORM("레이어 오브젝트가 유효하지 않아 함수 목적을 달성하지 못했습니다. 이는 치명적인 시도일 수 있습니다."));
        // 2. ??? ????.
        return;
    }
    // 1. 0???? ??????? ????? ?ε??? ????.
    if ( layer_obj->current_tab_index > 0 ) --layer_obj->current_tab_index;
    // 2. ??? ??????? ???????? ??? ??? ?ε????? ????????.
    else layer_obj->current_tab_index = layer_obj->tab_length;
}



// ????????? ????? ??? ??????? //
// ????????? ????? ??? ??????? ??????.
struct type$KeyboardInterface$Layer$layer_direction_obj_t method$KeyboardInterface$Layer$new_layer_direction_obj(
    uint16_t use_custom_direction_length
)
{
    // 1. ???? ????.
    if ( !use_custom_direction_length ) use_custom_direction_length = DEFAULT_LAYER_DIRECTION_LENGTH;
    // 2. ??????? ???.
    return(
        (struct type$KeyboardInterface$Layer$layer_direction_obj_t)
        {
            .max_length = use_custom_direction_length,
            .current_direction = 0,
            .layer_objs = malloc(
                sizeof(struct type$KeyboardInterface$Layer$layer_obj_t) * use_custom_direction_length
            ),
        }
    );
}
// ????????? ????? ??? ???????, ?????? ???.
uint8_t method$KeyboardInterface$Layer$layer_direction_move_to_down(
    struct type$KeyboardInterface$Layer$layer_direction_obj_t* const layer_direction_obj,
    const struct type$KeyboardInterface$Layer$layer_obj_t down_layer
)
{
    // 1. ???? ???????? ??쿡??.
    if (
        layer_direction_obj->layer_objs
    )
    {
        // 1. ???? ???? ??????? ??? move.
        if ( layer_direction_obj->current_direction < (signed)(layer_direction_obj->max_length-1) )
        {
            // 0. ??? ?????? ???.
            ++layer_direction_obj->current_direction;
            // 1. ????? ??? ???.
            layer_direction_obj->layer_objs[layer_direction_obj->current_direction] = down_layer;
            // 2. ???? ???.
            return( 1 );
        }
        // 2. ??? ??? ???.
        else
        {
            // 1. ??? ???? ???.
            struct type$KeyboardInterface$Layer$layer_obj_t* new_direction_space = realloc(
                layer_direction_obj->layer_objs,
                sizeof(struct type$KeyboardInterface$Layer$layer_obj_t) * ++layer_direction_obj->max_length
            );
            // 2. ??? ??? ???? ??.
            if ( new_direction_space )
            {
                // 1. ???? ???.
                layer_direction_obj->layer_objs = new_direction_space;
                // 2. ????? ??? ?????? ???.
                if ( layer_direction_obj->max_length > 1 ) ++layer_direction_obj->current_direction;
                else layer_direction_obj->current_direction = 0;
                // 3. ????? ??? ???.
                layer_direction_obj->layer_objs[layer_direction_obj->current_direction] = down_layer;
                // 4. ???? ???.
                return( 1 );
            }
            // 3. ??? ??? ???? ??.
            else
            {
                // 1. ??? ???? ???? ???????.
                --layer_direction_obj->max_length;
                // 2. ???? ?α?.
                // DebugSys.error(DEBUGSYS_LOG_FORM("????? ??? ????????? ???????? ?????? ?????? ???? ????? ????????? ??????????? ????? ??? ?????? ??????? ??????."));
                DebugSys.error(DEBUGSYS_LOG_FORM("realloc 함수가 메모리 할당에 실패했습니다. 개발자는 이에 대응하는 예외처리를 작성해야합니다."));
                // 2. ???? ???.
                return( 0 );
            }
        }
    }
    // 2. ???? ????????? ???? ???.
    else
    {
        // 0. ???? ?α?.
        // DebugSys.error(DEBUGSYS_LOG_FORM("????? ??? ????????? ???? ????????? ???? ?????? ??? ??? 0???? ????? ??? ?????? ??????? ??????."));
        DebugSys.error(DEBUGSYS_LOG_FORM("레이어 경로 오브젝트가 유효하지 않아 함수 목적을 달성하지 못했습니다. 이러한 시도는 치명적일 수 있습니다."));
        // 1. ???? ???.
        return( 0 );
    }
}
// ????????? ????? ??? ???????, ?????? ???.
uint8_t method$KeyboardInterface$Layer$layer_direction_move_to_up(
    struct type$KeyboardInterface$Layer$layer_direction_obj_t* const layer_direction_obj
)
{
    // 1. ??? ??? ???? ???.
    if ( layer_direction_obj->layer_objs )
    {
        // 1. ?????? ??? ???????? ???.
        if ( layer_direction_obj->current_direction )
        {
            // 1. ?????? ???.
            --layer_direction_obj->current_direction;
            // 2. ???? ???.
            return( 1 );
        }
        // 2. ?????? ??? ????? ???.
        else
        {
            // 1. ??? ?α?.
            // DebugSys.warn(DEBUGSYS_LOG_FORM("????? ??? ????????? ??δ? ??? ????? ??ο? ??? ?????? ??????? ??????. ????? ??? ?????? ??????? ???????? ??????????? ??????."));
            DebugSys.warn(DEBUGSYS_LOG_FORM("레이어 경로 오브젝트는 이미 최상위 경로에 있으므로 함수 목적을 달성할 수 없었지만 치명적이진 않습니다."));
            // 2. ???? ???.
            return( 1 );
        }
    }
    // 2. ???? ????????? ???? ???.
    else
    {
        // 1. ???? ?α?.
        // DebugSys.error(DEBUGSYS_LOG_FORM("????? ??? ????????? ?????? ????????? ??? ??θ? ?????? ??????? ???????. ????? ????? ??????? ?? ??????."));
        DebugSys.error(DEBUGSYS_LOG_FORM("레이어 오브젝트는 유효하지 않아 함수 목적을 달성하지 못했습니다. 이러한 시도는 치명적일 수 있습니다."));
        // 2. ???? ???.
        return( 0 );
    }
}



// ??? //
// ???? ??? ?????? ???? ??????? ???.
const uint8_t* method$KeyboardInterface$Layer$select_type_to_str( const enum enum$KeyboardInterface$Layer$select_obj_type type )
{
    switch ( type )
    {
        case KBI_type_btn : return( TEXT_TO_STR(KBI_type_btn) );
        case KBI_type_scroll : return( TEXT_TO_STR(KBI_type_scroll) );
        case KBI_type_textbox : return( TEXT_TO_STR(KBI_type_textbox) );
        case KBI_type_window : return( TEXT_TO_STR(KBI_type_window) );
        default : return( TEXT_TO_STR(KBI_type_null) );
    }
}
// ????????? ????? ???? ??????? ???.
const uint8_t* method$KeyboardInterface$Key$interface_key_to_str( const enum enum$KeyboardInterface$Key$interface_key key )
{
    switch ( key )
    {
        case KBI_click_arrow_bottom : return( TEXT_TO_STR(KBI_click_arrow_bottom) );
        case KBI_click_arrow_left : return( TEXT_TO_STR(KBI_click_arrow_left) );
        case KBI_click_arrow_right : return( TEXT_TO_STR(KBI_click_arrow_right) );
        case KBI_click_arrow_top : return( TEXT_TO_STR(KBI_click_arrow_top) );
        case KBI_click_backspace : return( TEXT_TO_STR(KBI_click_backspace) );
        case KBI_click_delete : return( TEXT_TO_STR(KBI_click_delete) );
        case KBI_click_enter : return( TEXT_TO_STR(KBI_click_enter) );
        case KBI_click_esc : return( TEXT_TO_STR(KBI_click_esc) );
        case KBI_click_F1 : return( TEXT_TO_STR(KBI_click_F1) );
        case KBI_click_F2 : return( TEXT_TO_STR(KBI_click_F2) );
        case KBI_click_tab : return( TEXT_TO_STR(KBI_click_tab) );
        default : return( TEXT_TO_STR(KBI_click_null) );
    }
}



// ????귯?? ???? //
struct class$KeyboardInterface
{
    struct _Tab
    {
        void(*const tab_index_writer_init)(void);
        type$KeyboardInterface$Layer$tab_index_t(*const tab_index_writer)(void);
    } Tab;


    struct _Key
    {
        enum enum$KeyboardInterface$Key$interface_key(*const get_key_state)( const key_code_t key );


        const uint8_t*(*const interface_key_to_str)( enum enum$KeyboardInterface$Key$interface_key key );
    } Key;

    
    struct _Layer
    {
        uint8_t(*const check_layer_obj)( const struct type$KeyboardInterface$Layer$layer_obj_t layer_obj );
        uint8_t(*const check_layer_direction_obj)( const struct type$KeyboardInterface$Layer$layer_direction_obj_t layer_obj );


        void(*const new_select_obj_init)(void);
        struct type$KeyboardInterface$Layer$select_obj_t(*const new_select_obj)(
            const enum enum$KeyboardInterface$Layer$select_obj_type type,
            const struct type$KeyboardInterface$pos_t dot_1, const struct type$KeyboardInterface$pos_t dot_2,
            const uint8_t is_active
        );


        struct type$KeyboardInterface$Layer$layer_obj_t(*const new_layer_obj)(
            const type$KeyboardInterface$Layer$tab_index_t tab_length,
            const type$KeyboardInterface$Layer$tab_index_t start_tab,
            const uint8_t is_update_only_this_window
        );
        void(*const insert_select_obj_to_layer)(
            struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
            const struct type$KeyboardInterface$Layer$select_obj_t select_obj
        );
        struct type$KeyboardInterface$Layer$select_obj_t(*const get_select_obj_of_layer)(
            struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
            const type$KeyboardInterface$Layer$tab_index_t index
        );
        void(*const edit_select_obj_of_layer)(
            struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj,
            const type$KeyboardInterface$Layer$tab_index_t index,
            const struct type$KeyboardInterface$Layer$select_obj_t select_obj
        );
        void(*const layer_obj_next_index)(
            struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj
        );
        void(*const layer_obj_previous_index)(
            struct type$KeyboardInterface$Layer$layer_obj_t* const layer_obj
        );


        struct type$KeyboardInterface$Layer$layer_direction_obj_t(*const new_layer_direction_obj)(
            uint16_t use_custom_direction_length
        );
        uint8_t(*const layer_direction_move_to_down)(
            struct type$KeyboardInterface$Layer$layer_direction_obj_t* const layer_direction_obj,
            const struct type$KeyboardInterface$Layer$layer_obj_t down_layer
        );
        uint8_t(*const layer_direction_move_to_up)(
            struct type$KeyboardInterface$Layer$layer_direction_obj_t* const layer_direction_obj
        );


        const uint8_t*(*const select_type_to_str)( enum enum$KeyboardInterface$Layer$select_obj_type type );
    } Layer;
} KeyboardInterface = {
    .Tab = {
        .tab_index_writer_init = method$KeyboardInterface$Tab$tab_index_writer_init,
        .tab_index_writer = method$KeyboardInterface$Tab$tab_index_writer,
    },

    .Key = {
        .get_key_state = method$KeyboardInterface$Key$get_key_state,

        .interface_key_to_str = method$KeyboardInterface$Key$interface_key_to_str,
    },
    
    .Layer = {
        .check_layer_obj = method$KeyboardInterface$Layer$check_layer_obj,
        .check_layer_direction_obj = method$KeyboardInterface$Layer$check_layer_direction_obj,

        .new_select_obj_init = method$KeyboardInterface$Layer$new_select_obj_init,
        .new_select_obj = method$KeyboardInterface$Layer$new_select_obj,

        .new_layer_obj = method$KeyboardInterface$Layer$new_layer_obj,
        .insert_select_obj_to_layer = method$KeyboardInterface$Layer$insert_select_obj_to_layer,
        .get_select_obj_of_layer = method$KeyboardInterface$Layer$get_select_obj_of_layer,
        .edit_select_obj_of_layer = method$KeyboardInterface$Layer$edit_select_obj_of_layer,
        .layer_obj_next_index = method$KeyboardInterface$Layer$layer_obj_next_index,
        .layer_obj_previous_index = method$KeyboardInterface$Layer$layer_obj_previous_index,

        .new_layer_direction_obj = method$KeyboardInterface$Layer$new_layer_direction_obj,
        .layer_direction_move_to_down = method$KeyboardInterface$Layer$layer_direction_move_to_down,
        .layer_direction_move_to_up = method$KeyboardInterface$Layer$layer_direction_move_to_up,

        .select_type_to_str = method$KeyboardInterface$Layer$select_type_to_str,
    },
};
