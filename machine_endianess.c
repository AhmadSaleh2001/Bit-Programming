#include <stdio.h>

int main() {

    int x = 1;
    char * first_byte = &x;
    char * second_byte = ((char*)&x) + 1;

    printf("first byte value: %d\n", *first_byte);
    printf("first byte address: %p\n", first_byte);

    printf("second byte value: %d\n", *second_byte);
    printf("second byte address: %p\n", second_byte);

    if(*first_byte == 1) {
        printf("Little endian machine\n");
    } else {
        printf("Big endian machine\n");
    }

    return 0;
}