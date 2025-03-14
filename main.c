#include "bitmap.h"

int main() {

    bitmap_t *bitmap = malloc(sizeof(bitmap_t));
    bitmap_init(bitmap, 64);
    bitmap_set_bit_at(bitmap, 0);
    bitmap_set_bit_at(bitmap, 3);
    bitmap_set_bit_at(bitmap, 8);
    bitmap_set_bit_at(bitmap, 31);
    bitmap_set_bit_at(bitmap, 32);

    bitmap_set_bit_at(bitmap, 63);
    bitmap_set_bit_at(bitmap, 45);

    char * buffer1 = bitmap_print(bitmap);
    printf("bitmap: %s\n", buffer1);

    printf("\n");
    bitmap_rshift32(bitmap, 2);
    char * buffer2 = bitmap_print(bitmap);
    printf("bitmap: %s\n", buffer2);

    bitmap_t *bitmap_cpy = malloc(sizeof(bitmap));
    bitmap_init(bitmap_cpy, 64);

    bitmap_copy(bitmap, bitmap_cpy, 0, 16);


    char * copied_bitmap_buffer = bitmap_print(bitmap_cpy);
    printf("copied bitmap: %s\n", copied_bitmap_buffer);

    printf("compare result: %d\n", bitmap_compare(bitmap, bitmap_cpy, 40));

    bitmap_t *wildcard = malloc(sizeof(bitmap_t));
    bitmap_init(wildcard, 64);
    bitmap_set_bit_at(wildcard, 0);
    bitmap_set_bit_at(wildcard, 1);
    printf("effective bit at 0: %d\n", bitmap_effective_bit_at(bitmap, wildcard, 0));
    printf("effective bit at 2: %d\n", bitmap_effective_bit_at(bitmap, wildcard, 2));
    printf("effective bit at 3: %d\n", bitmap_effective_bit_at(bitmap, wildcard, 3));

    bitmap_effective_print(bitmap, wildcard);

    uint32_t input_val = 0xAFBBCCDD;
    uint32_t prefix_val = 0xAABBCCDD;
    uint32_t wildcard_val = 0b1111;

    printf("prefix match result: %d\n", prefix32bit_match(input_val, prefix_val, wildcard_val, 1));


    return 0;
}