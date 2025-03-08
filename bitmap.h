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

typedef struct bitmap
{
    uint32_t *bit;
    uint16_t tsize; // number of bits
    uint16_t next;
} bitmap_t;

void bitmap_init(bitmap_t * bitmap, uint16_t tsize);

void bitmap_set_bit_at(bitmap_t * bitmap, uint16_t index);
void bitmap_unset_bit_at(bitmap_t * bitmap, uint16_t index);
bool bitmap_at(bitmap_t * bitmap, uint16_t index);

char * bitmap_print(bitmap_t * bitmap);