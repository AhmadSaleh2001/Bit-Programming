#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void bitmap_init(bitmap_t * bitmap, uint16_t tsize) {
    assert((tsize%sizeof(uint32_t)) == 0);
    uint16_t number_of_chunks = tsize / sizeof(uint32_t);
    bitmap->bits = calloc(number_of_chunks, sizeof(uint32_t));
    bitmap->tsize = tsize;
    bitmap->next = 0; // zero meaning NULL
}

int get_chunk_index(int bit_index) {
    return bit_index / sizeof(uint32_t);
}

int get_bit_index_in_chunk(int bit_index) {
    return sizeof(uint32_t) - (bit_index % sizeof(uint32_t));
}

void bitmap_set_bit_at(bitmap_t * bitmap, uint16_t index) {
    int chunk_index = get_chunk_index(index);
    int bit_index_in_chunk = get_bit_index_in_chunk(index);
    SET_BIT(bitmap->bits[chunk_index], 1<<bit_index_in_chunk);
}

void bitmap_unset_bit_at(bitmap_t * bitmap, uint16_t index) {
    int chunk_index = get_chunk_index(index);
    int bit_index_in_chunk = get_bit_index_in_chunk(index);
    UNSET_BIT32(bitmap->bits[chunk_index], 1<<bit_index_in_chunk);
}

bool bitmap_at(bitmap_t * bitmap, uint16_t index) {
    int chunk_index = get_chunk_index(index);
    int bit_index_in_chunk = get_bit_index_in_chunk(index);
    return IS_BIT_SET(bitmap->bits[chunk_index], 1<<bit_index_in_chunk);
}

char * bitmap_print(bitmap_t * bitmap) {
    static char buffer[OUTPUT_BUFFER_SIZE];
    memset(buffer, 0, sizeof buffer);

    uint16_t buffer_cursor = 0 ;
    uint16_t index, boolout;
    BITMAP_ITERATE_BEGIN(bitmap, 0, index, boolout) {
        if(index%8 == 0) {
            buffer_cursor += sprintf(buffer + buffer_cursor, " ");
        }
        buffer_cursor += sprintf(buffer + buffer_cursor, "%d", boolout);
    } BITMAP_ITERATE_END(bitmap, 0, index, boolout)

    return buffer;
}

// Endian indepened code functions

void copy(
    uint32_t * src, 
    uint32_t * dst, 
    int src_start_pos, 
    int dst_start_pos, 
    int count) {

    uint32_t src_value = htonl(*src);
    src_value>>=(32 - (src_start_pos + count));
    src_value<<=(32 - (src_start_pos + count));
    src_value<<=src_start_pos;
    *dst = htonl(src_value);
}

void print_binary(int x) {
    for(int i=31;i>=0;i--) {
        printf("%d", (x>>i)&1);
    }
    printf("\n");
}

uint32_t bit_generate_ones(uint8_t start, uint8_t end) {
    uint32_t ans = 0;

    printf("%d %d\n", start, end);
    start = 31 - start;
    end = 31 - end;
    printf("%d %d\n", start, end);

    for(uint32_t i=end;i<=start;i++) {
        ans|=(1ll<<i);
    }

    return ans;
}

bool uint32_bit_compare(uint32_t bit1, uint32_t bit2, uint8_t count) {
    int until = 32 - count;
    for(uint8_t i=31;i>=until;i--) {
        bool b1 = (bit1>>i)&1;
        bool b2 = (bit2>>i)&1;
        if(b1 != b2)return 0;
    }
    return 1;
}