void *func_800855D0(void);

unsigned int func_80085F5C(void **arena) {
    register unsigned int result asm("$16") = 0;
    void *first;

    asm("" : "+r"(result));
    if (arena == (void **)-1) {
        arena = (void **)func_800855D0();
    }
    first = *arena;
    if (first != 0) {
        result = *(unsigned int *)((unsigned char *)first + 4);
    }
    return result;
}
