#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>

void bitmap_init(bitmap_t * bitmap, uint16_t tsize) {
    assert((tsize%32) == 0);
    uint16_t number_of_chunks = tsize / 32;
    bitmap->bits = calloc(number_of_chunks, 32);
    bitmap->tsize = tsize;
    bitmap->next = 0; // zero meaning NULL
}

int get_chunk_index(int bit_index) {
    return bit_index / 32;
}

int get_bit_index_in_chunk(int bit_index) {
    return 31 - (bit_index % 32);
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

void bitmap_effective_print(bitmap_t * bitmap, bitmap_t * wildcard) {
    static char buffer[OUTPUT_BUFFER_SIZE];
    memset(buffer, 0, sizeof buffer);

    uint16_t buffer_cursor = 0 ;
    uint16_t index;
    bitmap_type_t effective_bit_output;
    BITMAP_EFFECTIVE_ITERATE_BEGIN(bitmap, wildcard, 0, index, effective_bit_output) {
        if(index%8 == 0) {
            buffer_cursor += sprintf(buffer + buffer_cursor, " ");
        }
        char actualChar = 'X';
        if(effective_bit_output == ONE)actualChar = '1';
        else if(effective_bit_output == ZERO)actualChar = '0';
        buffer_cursor += sprintf(buffer + buffer_cursor, "%c", actualChar);
    } BITMAP_EFFECTIVE_ITERATE_END(bitmap, wildcard, 0, index, effective_bit_output)

    printf("effective bitmap: %s\n", buffer);
    printf("bitmap: %s\n", bitmap_print(bitmap));
    printf("wildcard: %s\n", bitmap_print(wildcard));
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
    src_value>>=dst_start_pos;
    *dst = htonl(src_value);
}

void print_binary(uint32_t x) {
    for(int i=31;i>=0;i--) {
        printf("%d", (x>>i)&1);
    }
    printf("\n");
}

uint32_t bit_generate_ones(uint8_t start, uint8_t end) {
    uint32_t ans = 0;
    start = 31 - start;
    end = 31 - end;

    for(uint32_t i=end;i<=start;i++) {
        ans|=((uint32_t)1<<i);
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

bool uint32_bit_compare_v2(uint32_t bit1, uint32_t bit2, uint8_t count) {
    uint32_t msk = bit_generate_ones(0, count - 1);
    return (bit1&msk) == (bit2&msk);
}

void bitmap_lshift32(bitmap_t * bitmap, uint16_t count) {
    assert(count >= 0 && count <= 31);
    int cnt = 0;
    int end = bitmap->tsize/32;
    while(cnt < end - 1) {
        uint32_t currVal = bitmap->bits[cnt];
        currVal<<=count;
        uint32_t nextVal = bitmap->bits[cnt + 1];
        nextVal>>=(32 - count);
        bitmap->bits[cnt] = currVal | nextVal;
        cnt++;
    }
    bitmap->bits[cnt]<<=count;
}

void bitmap_rshift32(bitmap_t * bitmap, uint16_t count) {
    assert(count >= 0 && count <= 31);
    int cnt = bitmap->tsize/32 - 1;
    while(cnt > 0) {
        uint32_t currVal = bitmap->bits[cnt];
        currVal>>=count;
        uint32_t nextVal = bitmap->bits[cnt - 1];
        nextVal<<=(32 - count);
        bitmap->bits[cnt] = currVal | nextVal;
        cnt--;
    }
    bitmap->bits[0]>>=count;
}

void bitmap_copy(bitmap_t * src, bitmap_t * dst, uint16_t start_index, uint16_t count) {
    assert(src->tsize == dst->tsize);
    int end = src->tsize/32;
    for(int i=0;i<end;i++) {
        dst->bits[i] = src->bits[i];
    }
    
    int toBeRightShift = dst->tsize - (start_index + count);
    int toBeLeftShift = start_index + toBeRightShift;

    while(toBeRightShift > 0) {
        int mn = toBeRightShift > 31 ? 31 : toBeRightShift;
        bitmap_rshift32(dst, mn);
        toBeRightShift-=mn;
    }

    while(toBeLeftShift > 0) {
        int mn = toBeLeftShift > 31 ? 31 : toBeLeftShift;
        bitmap_lshift32(dst, mn);
        toBeLeftShift-=mn;
    }
}

bool bitmap_compare(bitmap_t * src, bitmap_t * dst, uint16_t count) {
    assert(src->tsize == dst->tsize);
    assert(src->tsize >= count);
    int cnt = 0 ;
    while(count > 0) {
        int mn = count > 32 ? 32 : count;
        count-=mn;
        if(!uint32_bit_compare_v2(src->bits[cnt], dst->bits[cnt], mn))return 0;
        cnt++;
    }

    return 1;
}

bitmap_type_t bitmap_effective_bit_at(bitmap_t * bitmap, bitmap_t * wildcard, uint16_t pos) {
    if(bitmap_at(wildcard, pos))return DONT_CARE;
    if(bitmap_at(bitmap, pos))return ONE;
    return ZERO;
}

bool prefix32bit_match(uint32_t input, uint32_t prefix, uint32_t wildcard, uint8_t prefix_len) {
    input = htonl(input);
    prefix = htonl(prefix);
    wildcard = htonl(wildcard);

    for(uint32_t i=0;i<prefix_len;i++) {
        uint32_t position = 1<<i;
        if(IS_BIT_SET(wildcard, position))continue;
        if(IS_BIT_SET(input, position) != IS_BIT_SET(prefix, position))return 0;
    }

    return 1;
}