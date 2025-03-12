#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define OUTPUT_BUFFER_SIZE 512
#define IS_BIT_SET(n, pos) (n & pos)
#define TOGGLE_BIT(n, pos) (n = n ^ pos)
#define COMPLEMENT8(num) (num = num ^ 0xFF)
#define COMPLEMENT32(num) (num = num ^ 0xFFFFFFFF)
#define COMPLEMENT16(num) (num = num ^ 0xFFFF)
#define COMPLEMENT64(num) (num = num ^ 0xFFFFFFFFFFFFFFFF)
#define UNSET_BIT32(n, pos) (n &= (~(pos & 0xFFFFFFFF)))
#define UNSET_BIT64(n, pos) (n &= (~(pos & 0xFFFFFFFFFFFFFFFF)))
#define UNSET_BIT16(n, pos) (n &= (~(pos & 0xFFFF)))
#define UNSET_BIT8(n, pos) (n &= (~(pos & 0xFF)))
#define SET_BIT(n, pos) (n |= pos)

#define BITMAP_ITERATE_BEGIN(bitmap_ptr, start_index, _index, boolout) \
    for(_index = start_index;_index < bitmap_ptr->tsize;_index++) { \
        boolout = bitmap_at(bitmap_ptr, _index);

#define BITMAP_ITERATE_END(bitmap_ptr, start_index, _index, boolout) }

typedef struct bitmap
{
    uint32_t *bits;
    uint16_t tsize; // number of bits
    uint16_t next;
} bitmap_t;

void bitmap_init(bitmap_t * bitmap, uint16_t tsize);

void bitmap_set_bit_at(bitmap_t * bitmap, uint16_t index);
void bitmap_unset_bit_at(bitmap_t * bitmap, uint16_t index);
bool bitmap_at(bitmap_t * bitmap, uint16_t index);

char * bitmap_print(bitmap_t * bitmap);

void copy(uint32_t * src, uint32_t * dst, int src_start_pos, int dst_start_pos, int count);

// Endian indepened code functions

void endian_independent_bitmap_set_bit_at(bitmap_t * bitmap, uint16_t index);

void print_binary(int x);

uint32_t bit_generate_ones(uint8_t start, uint8_t end);
bool uint32_bit_compare(uint32_t bit1, uint32_t bit2, uint8_t count);