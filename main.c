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

    return 0;
}