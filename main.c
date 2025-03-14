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

    printf("effective bitmap: %s\n", bitmap_effective_print(bitmap, wildcard));

    // uint32_t x1 = bit_generate_ones(2, 10);
    // print_binary(x1);

    // uint32_t x2 = bit_generate_ones(2, 12);
    // print_binary(x2);

    // printf("compare: %d\n", uint32_bit_compare(x1, x2, 5));
    // printf("compare: %d\n", uint32_bit_compare_v2(x1, x2, 5));

    return 0;
}