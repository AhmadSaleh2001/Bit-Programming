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

#define BITMAP_EFFECTIVE_ITERATE_BEGIN(bitmap_ptr, wilcard_ptr, start_index, _index, effective_bit_output) \
    for(_index = start_index;_index < bitmap_ptr->tsize;_index++) { \
        effective_bit_output = bitmap_effective_bit_at(bitmap_ptr, wilcard_ptr, _index);

#define BITMAP_EFFECTIVE_ITERATE_END(bitmap_ptr, wilcard_ptr, start_index, _index, effective_bit_output) }

static inline uint32_t
LSHIFT(uint32_t N, uint16_t n)
{
  if (n == 32)
    return 0;
 
  N <<= n;
  return N;
}
 
static inline uint32_t
 
RSHIFT(uint32_t N, uint16_t n)
{
  if (n == 32)
    return 0;
 
  N >>= n;
  return N;
}

typedef enum {
  ZERO,
  ONE,
  DONT_CARE
} bitmap_type_t;

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
void bitmap_effective_print(bitmap_t * bitmap, bitmap_t * wildcard);

void copy(uint32_t * src, uint32_t * dst, int src_start_pos, int dst_start_pos, int count);

// Endian indepened code functions

void endian_independent_bitmap_set_bit_at(bitmap_t * bitmap, uint16_t index);

void print_binary(uint32_t x);

uint32_t bit_generate_ones(uint8_t start, uint8_t end);
bool uint32_bit_compare(uint32_t bit1, uint32_t bit2, uint8_t count);
bool uint32_bit_compare_v2(uint32_t bit1, uint32_t bit2, uint8_t count);

void bitmap_lshift32(bitmap_t * bitmap, uint16_t count);
void bitmap_rshift32(bitmap_t * bitmap, uint16_t count);

void bitmap_copy(bitmap_t * src, bitmap_t * dst, uint16_t start_index, uint16_t count);

bool bitmap_compare(bitmap_t * src, bitmap_t * dst, uint16_t count);

bitmap_type_t bitmap_effective_bit_at(bitmap_t * bitmap, bitmap_t * wildcard, uint16_t pos);


// mask: when we have 0, meaning dont care
// wildcard: when we have 1, meaning dont care
bool prefix32bit_match(uint32_t input, uint32_t prefix, uint32_t wildcard, uint8_t prefix_len);
bool prefix32bit_match_enhance(uint32_t input, uint32_t prefix, uint32_t wildcard, uint8_t prefix_len);
void prefix32bit_apply_mask(uint32_t *input, uint32_t mask, uint8_t mask_len);
void bitmap_inverse(bitmap_t *bitmap, uint16_t count);

void bitmap_swap_bits(bitmap_t *bitmap, uint16_t pos1, uint16_t pos2);
void bitmap_reverse (bitmap_t *bitmap, uint16_t count);

bitmap_t * GI_to_bitmap(char * giant_integer, uint16_t number_of_digits);