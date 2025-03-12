#include "bitmap.h"

int main() {

    bitmap_t *bitmap = malloc(sizeof(bitmap));
    bitmap_init(bitmap, 64);
    bitmap_set_bit_at(bitmap, 0);
    bitmap_set_bit_at(bitmap, 3);
    bitmap_set_bit_at(bitmap, 8);
    bitmap_set_bit_at(bitmap, 31);

    char * buffer = bitmap_print(bitmap);
    printf("bitmap: %s\n", buffer);

    uint32_t x1 = bit_generate_ones(2, 10);
    print_binary(x1);

    uint32_t x2 = bit_generate_ones(2, 12);
    print_binary(x2);

    printf("compare: %d\n", uint32_bit_compare(x1, x2, 5));
    printf("compare: %d\n", uint32_bit_compare_v2(x1, x2, 5));

    return 0;
}