/*
    [���̺귯��]
    DebubSys.h

    [����]
    ������ ����, ��� ����� ���� �⺻���� �ý��� ���� ���̺귯��.
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

// �α� ����Ʈ ���� ������Ʈ.
struct type$DebugSys$debugs_t
{
    uint32_t max_length;
    uint32_t index;
    uint8_t** logs;
    enum enum$DebugSys$debug_type* log_types;
} val$DebugSys$debugs = {
    // ����, DebugSys ����� ���� ���� ����.
    .max_length = DEFAULT_DEBUGSYS_MAX_NUM_OF_STR,
    .index = 0,
    .logs = NULL,
    .log_types = NULL,
};

// ���� �α� ���� ������Ʈ.
struct type$DebugSys$debug_t
{
    const uint8_t* const log;
    const enum enum$DebugSys$debug_type log_type;
};



// ����, DebugSys �ʱ�ȭ ����.
static uint8_t val$DebugSys$is_inited = 0;


// DebugSys �ʱ�ȭ �Լ�.
struct type$DebugSys$state_t method$DebugSys$init( uint32_t number_of_max_str )
{
    if ( val$DebugSys$is_inited )
    {
        return(
            (struct type$DebugSys$state_t)
            {
                .success = 0,
                .log = (uint8_t*)"�̹� �ʱ�ȭ�� �Ǿ��ֽ��ϴ�",
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
        
        // 1. �Ҵ� ���� ó��.
        if ( !new_strs_space || !new_types_space )
        {
            if ( new_strs_space ) free(new_strs_space);
            if ( new_types_space ) free(new_types_space);

            return(
                (struct type$DebugSys$state_t)
                {
                    .success = 0,
                    .log = (const uint8_t*)"�޸� �Ҵ� ����.",
                }
            );
        }
        // 2. �Ҵ� ���� ��.
        else
        {
            val$DebugSys$is_inited = 1;
            val$DebugSys$debugs.logs = new_strs_space;
            val$DebugSys$debugs.log_types = new_types_space;

            // 1. ���� ��ȯ.
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
// DebugSys �޸� ���� �Լ�.
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

// ���� �α� �߰� �Լ�.
void method$DebugSys$error( uint8_t* const log )
{
    // init�� �Ǿ��ִ� ��쿡��.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. �����÷ο� ����.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. ���� �α� �߰�.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_error;
    }
    // init�� �Ǿ����� ������ �׳� ����.
    else
    {
        return;
    }
}

// ��� �α� �߰� �Լ�.
void method$DebugSys$warn( uint8_t* const log )
{
    // init�� �Ǿ��ִ� ��쿡��.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. �����÷ο� ����.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. ���� �α� �߰�.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_warn;
        // 3. ���� ȣ�� �� �ʿ��� �ε����� ������Ʈ.
        val$DebugSys$debugs.index++;
    }
    // init�� �Ǿ����� ������ �׳� ����.
    else
    {
        return;
    }
}

// �˸�, ���, ǥ��, ���� �α� �߰� �Լ�.
void method$DebugSys$info( uint8_t* const log )
{
    // init�� �Ǿ��ִ� ��쿡��.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. �����÷ο� ����.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. ���� �α� �߰�.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_info;
        // 3. ���� ȣ�� �� �ʿ��� �ε����� ������Ʈ.
        val$DebugSys$debugs.index++;
    }
    // init�� �Ǿ����� ������ �׳� ����.
    else
    {
        return;
    }
}

// ����� �α� �߰� �Լ�.
void method$DebugSys$debug( uint8_t* const log )
{
    // init�� �Ǿ��ִ� ��쿡��.
    if ( val$DebugSys$debugs.logs && val$DebugSys$debugs.log_types )
    {
        // 1. �����÷ο� ����.
        if ( val$DebugSys$debugs.index >= val$DebugSys$debugs.max_length )
        {
            val$DebugSys$debugs.index = 0;
        }
        // 2. ���� �α� �߰�.
        val$DebugSys$debugs.logs[val$DebugSys$debugs.index] = log;
        val$DebugSys$debugs.log_types[val$DebugSys$debugs.index] = DebugSys_type_debug;
        // 3. ���� ȣ�� �� �ʿ��� �ε����� ������Ʈ.
        val$DebugSys$debugs.index++;
    }
    // init�� �Ǿ����� ������ �׳� ����.
    else
    {
        return;
    }
}

// �α� ����Ʈ ��ȯ.
const struct type$DebugSys$debugs_t method$DebugSys$get_log_list()
{
    return(
        (const struct type$DebugSys$debugs_t)
        val$DebugSys$debugs
    );    
}

// �α� ��������.
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

// �α� ���� ������ ��ȯ �Լ�.
uint8_t*const method$DebugSys$log_form( uint8_t* const path_str, uint64_t line_num, uint8_t* const static_str )
{
    // 1. �ּ� Ȯ��.
    if ( !path_str || !static_str )
    {
        // 1. �Լ� ����.
        return( 0 );
    }

    // 2. ���� �ѹ� ���ڿ� ���� ���ϱ�.
    uint8_t line_str[23] = {0};
    sprintf(line_str, "%llu", line_num);
    const uint8_t line_str_len = strlen(line_str);

    // 2. ���� �޸� �Ҵ�.
    uint8_t* str_space = Etc.new_static_mem_space(2 + strlen(path_str) + 3 + ( line_str_len ) + 4 + strlen(static_str) + 1);

    // 2. �α� ���� ����.
    sprintf(str_space, "[\"%s\"][%lld] : %s", path_str, line_num, static_str);

    // 3. ��ȯ.
    return( str_space );
}



// ���̺귯�� ��üȭ //
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
