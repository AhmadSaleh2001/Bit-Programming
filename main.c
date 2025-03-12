#include "bitmap.h"

int main() {

    // bitmap_t *bitmap = malloc(sizeof(bitmap));
    // bitmap_init(bitmap, 64);
    // bitmap_set_bit_at(bitmap, 0);
    // bitmap_set_bit_at(bitmap, 3);
    // bitmap_set_bit_at(bitmap, 8);
    // bitmap_set_bit_at(bitmap, 31);

    // char * buffer = bitmap_print(bitmap);
    // printf("bitmap: %s\n", buffer);

    uint32_t x = 0x01020304;
    uint32_t z = 0;

    copy(&x, &z, 8, 16, 8);
    
    printf("hex1: 0x%x\n", x);
    printf("hex2: 0x%x\n", z);

    return 0;
}