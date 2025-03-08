#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void bitmap_init(bitmap_t * bitmap, uint16_t tsize) {
    assert((tsize%sizeof(uint32_t)) == 0);
    uint16_t number_of_chunks = tsize / sizeof(uint32_t);
    bitmap->bit = calloc(number_of_chunks, sizeof(uint32_t));
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
    SET_BIT(bitmap->bit[chunk_index], 1<<bit_index_in_chunk);
}

void bitmap_unset_bit_at(bitmap_t * bitmap, uint16_t index) {
    int chunk_index = get_chunk_index(index);
    int bit_index_in_chunk = get_bit_index_in_chunk(index);
    UNSET_BIT32(bitmap->bit[chunk_index], 1<<bit_index_in_chunk);
}

bool bitmap_at(bitmap_t * bitmap, uint16_t index) {
    int chunk_index = get_chunk_index(index);
    int bit_index_in_chunk = get_bit_index_in_chunk(index);
    return IS_BIT_SET(bitmap->bit[chunk_index], 1<<bit_index_in_chunk);
}

char * bitmap_print(bitmap_t * bitmap) {
    uint16_t index;

    static char buffer[OUTPUT_BUFFER_SIZE];
    memset(buffer, 0, sizeof buffer);

    uint16_t buffer_cursor = 0 ;

    for(index = 0;index < bitmap->tsize;index++) {
        if(index%8 == 0) {
            buffer_cursor += sprintf(buffer + buffer_cursor, " ");
        }
        buffer_cursor += sprintf(buffer + buffer_cursor, "%d", bitmap_at(bitmap, index));
    }

    return buffer;
}