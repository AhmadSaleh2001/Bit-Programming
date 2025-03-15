# Bitmap Operations Project

This project provides a set of functions to manipulate and work with bitmaps in C. A bitmap is a structure that holds a sequence of bits and allows operations like setting, unsetting, toggling, shifting, and comparing bits. It includes functionalities for bitmap manipulation, bitwise operations, and bit-level optimizations.

## Features

- **Bitmap Creation & Initialization**: Allows for the creation of bitmaps of various sizes and initializes them.
- **Bitwise Operations**: Set, unset, toggle, and shift bits, as well as complementing the entire bitmap.
- **Iterating over Bitmaps**: Functions to iterate over bitmaps, including effective iteration using wildcards.
- **Endian Independent Functions**: Functions that work in an endian-independent manner.
- **Prefix Matching**: Ability to match prefixes in 32-bit values.
- **Conversion to/from Giant Integers**: Convert giant integer strings to bitmaps and back.
- **Bitmap Reversal & Swapping**: Reverse and swap bits within the bitmap.

## Key Structures

### `bitmap_t`
```c
typedef struct bitmap {
    uint32_t *bits;  // Pointer to the bitmap data
    uint16_t tsize;  // Total number of bits in the bitmap
    uint16_t next;   // Not used
} bitmap_t;
