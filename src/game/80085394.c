void *func_80085394(unsigned char **arena, unsigned char *first, unsigned int first_size, unsigned int second_size) {
    register int mask asm("$2") = -2;
    register unsigned char *second asm("$3");
    register unsigned int first_extent asm("$6") = first_size;
    register unsigned int second_extent asm("$7") = second_size;
    unsigned char *next;

    *(unsigned int *)(first + 4) = first_size;
    first_extent = (first_extent & mask) + 12;
    second = first + first_extent;
    *(unsigned int *)(second + 4) = second_size;
    asm volatile("" : : : "memory");
    second_extent &= mask;
    asm("" : "+r"(second_extent));
    second_extent += 12;
    asm("" : "+r"(second_extent));
    *(unsigned char ***)(second + 8) = arena;
    *(unsigned char **)(second + 0) = first;
    next = second + second_extent;
    if (next < *arena) {
        *(unsigned char **)(next + 0) = second;
    }
    return second;
}
