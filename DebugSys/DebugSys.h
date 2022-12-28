/*
    [라이브러리]
    DebubSys.h

    [설명]
    디버깅과 에러, 경고 출력을 위한 기본적인 시스템 제공 라이브러리.
*/

#pragma once
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../Etc/Etc.h"


#define DEFAULT_DEBUGSYS_MAX_NUM_OF_STR 5000


// #define DEBUGSYS_LOG_FORM( LOG_STR ) __FILE__"["__LINE__"] : "LOG_STR
// #define DEBUGSYS_LOG_FORM( LOG_STR ) ((uint8_t* const)(__FILE__ " : " LOG_STR))
// #define DEBUGSYS_LOG_FORM( LOG_STR ) ((uint8_t* const)(__FILE__ " ["  "] : " LOG_STR))
// #define DEBUGSYS_LOG_FORM( LOG_STR )   
#define DEBUGSYS_LOG_FORM( LOG_STR )   (DebugSys.log_form(__FILE__, __LINE__, LOG_STR))



enum enum$DebugSys$debug_type
{
    DebugSys_type_null,
    DebugSys_type_error,
    DebugSys_type_warn,
    DebugSys_type_info,
    DebugSys_type_debug,
};

struct type$DebugSys$state_t
{
    uint8_t success;
    const uint8_t* log;
};

// 로그 리스트 정보 오브젝트.
struct type$DebugSys$debugs_t
{
    uint32_t max_length;
    uint32_t index;
    uint8_t** logs;
    enum enum$DebugSys$debug_type* log_types;
} val$DebugSys$debugs = {
    // 전역, DebugSys 디버그 내용 저장 변수.
    .max_length = DEFAULT_DEBUGSYS_MAX_NUM_OF_STR,
    .index = 0,
    .logs = NULL,
    .log_types = NULL,
};

// 단일 로그 정보 오브젝트.
struct type$DebugSys$debug_t
{
    const uint8_t* const log;
    const enum enum$DebugSys$debug_type log_type;
};



// 전역, DebugSys 초기화 여부.
static uint8_t val$DebugSys$is_inited = 0;


// DebugSys 초기화 함수.
struct type$DebugSys$state_t method$DebugSys$init( uint32_t number_of_max_str )
{
    if ( val$DebugSys$is_inited )
    {
        return(
            (struct type$DebugSys$state_t)
            {
                .success = 0,
                .log = (uint8_t*)"이미 초기화가 되어있습니다",
            }
        );
    }
    else
    {
        if ( !number_of_max_str ) number_of_max_str = DEFAULT_DEBUGSYS_MAX_NUM_OF_STR;
        uint8_t** new_strs_space = (uint8_t**)malloc(
            sizeof(uint8_t*) * number_of_max_str
        );
        enum enum$DebugSys$debug_type* new_types_space = (enum enum$DebugSys$debug_type*)malloc(
            sizeof(enum enum$DebugSys$debug_type) * number_of_max_str
        );
        
        // 1. 할당 유무 처리.
        if ( !new_strs_space || !new_types_space )
        {
            if ( new_strs_space ) free(new_strs_space);
            if ( new_types_space ) free(new_types_space);

            return(
                (struct type$DebugSys$state_t)
                {
                    .success = 0,
                    .log = (const uint8_t*)"메모리 할당 실패.",
                }
            );
        }
        // 2. 할당 성공 시.
        else
        {
            val$DebugSys$is_inited = 1;
            val$DebugSys$debugs.logs = new_strs_space;
            val$DebugSys$debugs.log_types = new_types_space;

            // 1. 성공 반환.
            return(
                (struct type$DebugSys$state_t)
                {
                    .success = 1,
                    .log = 0,
                }
            );
        }
    }
}
// DebugSys 메모리 해제 함수.
struct type$DebugSys$state_t method$DebugSys$uninit()
{
    if ( val$DebugSys$debugs.logs ) free(val$DebugSys$debugs.logs);
    if ( val$DebugSys$debugs.log_types ) free(val$DebugSys$debugs.log_types);
    val$DebugSys$is_inited = 0;

    return(
        (struct type$DebugSys$state_t)
        {
            .success = 1,
            .log = 0,
        }
    );
}

// 에러 로그 추가 함수.
void method$DebugSys$error( uint8_t* const log )
{
    // init이 되어있는 경우에만.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. 오버플로우 방지.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. 에러 로그 추가.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_error;
    }
    // init이 되어있지 않으면 그냥 종료.
    else
    {
        return;
    }
}

// 경고 로그 추가 함수.
void method$DebugSys$warn( uint8_t* const log )
{
    // init이 되어있는 경우에만.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. 오버플로우 방지.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. 에러 로그 추가.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_warn;
        // 3. 다음 호출 시 필요한 인덱스로 업데이트.
        val$DebugSys$debugs.index++;
    }
    // init이 되어있지 않으면 그냥 종료.
    else
    {
        return;
    }
}

// 알림, 명시, 표시, 정보 로그 추가 함수.
void method$DebugSys$info( uint8_t* const log )
{
    // init이 되어있는 경우에만.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. 오버플로우 방지.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. 에러 로그 추가.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_info;
        // 3. 다음 호출 시 필요한 인덱스로 업데이트.
        val$DebugSys$debugs.index++;
    }
    // init이 되어있지 않으면 그냥 종료.
    else
    {
        return;
    }
}

// 디버그 로그 추가 함수.
void method$DebugSys$debug( uint8_t* const log )
{
    // init이 되어있는 경우에만.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. 오버플로우 방지.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. 에러 로그 추가.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_debug;
        // 3. 다음 호출 시 필요한 인덱스로 업데이트.
        val$DebugSys$debugs.index++;
    }
    // init이 되어있지 않으면 그냥 종료.
    else
    {
        return;
    }
}

// 로그 리스트 반환.
const struct type$DebugSys$debugs_t method$DebugSys$get_log_list()
{
    return(
        (const struct type$DebugSys$debugs_t)
        val$DebugSys$debugs
    );    
}

// 로그 가져오기.
const struct type$DebugSys$debug_t method$DebugSys$get_log( const uint32_t index )
{
    return(
        (struct type$DebugSys$debug_t)
        {
            .log = val$DebugSys$debugs.logs[index],
            .log_type = val$DebugSys$debugs.log_types[index],
        }
    );
}

// 로그 형식 폼으로 변환 함수.
uint8_t*const method$DebugSys$log_form( uint8_t* const path_str, uint64_t line_num, uint8_t* const static_str )
{
    // 1. 주소 확인.
    if ( !path_str || !static_str )
    {
        // 1. 함수 종료.
        return( 0 );
    }

    // 2. 라인 넘버 문자열 길이 구하기.
    uint8_t line_str[23] = {0};
    sprintf(line_str, "%llu", line_num);
    const uint8_t line_str_len = strlen(line_str);

    // 2. 전역 메모리 할당.
    uint8_t* str_space = Etc.new_static_mem_space(2 + strlen(path_str) + 3 + ( line_str_len ) + 4 + strlen(static_str) + 1);

    // 2. 로그 형식 적용.
    sprintf(str_space, "[\"%s\"][%lld] : %s", path_str, line_num, static_str);

    // 3. 반환.
    return( str_space );
}



// 라이브러리 객체화 //
struct class$DebugSys
{
    struct _library
    {
        struct type$DebugSys$state_t(*init)( uint32_t number_of_max_str );
        struct type$DebugSys$state_t(*const uninit)(void);
    } library;
    
    void(*const error)( uint8_t* const log );
    void(*const warn)( uint8_t* const log );
    void(*const info)( uint8_t* const log );
    void(*const debug)( uint8_t* const log );
    uint8_t*const(*const log_form)( uint8_t* const path_str, uint64_t line_num, uint8_t* const static_str );

    const struct type$DebugSys$debugs_t(*const get_log_list)(void);
    const struct type$DebugSys$debug_t(*const get_log)( const uint32_t index );
} DebugSys = {
    .library = {
        .init = method$DebugSys$init,
        .uninit = method$DebugSys$uninit,
    },
    .error = method$DebugSys$error,
    .warn = method$DebugSys$warn,
    .info = method$DebugSys$info,
    .debug = method$DebugSys$debug,
    .log_form = method$DebugSys$log_form,
    
    .get_log_list = method$DebugSys$get_log_list,
    .get_log = method$DebugSys$get_log,
};
