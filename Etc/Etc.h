/*
    [라이브러리]
    Etc.h
*/
#pragma once
#include <stdint.h>
#include <malloc.h>

#define TEXT_TO_STR( TEXT ) #TEXT

uint64_t method$class_Etc$struct_to_8byte( uint8_t null, ... )
{
    return( *((uint64_t*)&null+1) );
}

// 전역 메모리 공간 생성자.
void* method$Etc$new_static_mem_space( const uint64_t size_byte )
{
    return( calloc(1, size_byte) );
}

struct class$Etc
{
    uint64_t(*const struct_to_8byte)( uint8_t null, ... );
    void*(*const new_static_mem_space)( const uint64_t size_byte );
} Etc = {
    .struct_to_8byte = method$class_Etc$struct_to_8byte,
    .new_static_mem_space = method$Etc$new_static_mem_space,
};
