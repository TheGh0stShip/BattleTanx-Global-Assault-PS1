extern void *D_800B90EC;

void *func_800A18EC(void *callback) {
    register unsigned char *cursor asm("$3") = (unsigned char *)&D_800B90EC;
    register void *previous asm("$2");

    asm("" : "+r"(cursor));
    previous = *(void **)cursor;
    asm("" : "+r"(previous));
    cursor -= 48;
    asm("" : "+r"(cursor));
    *(void **)(cursor + 48) = callback;
    return previous;
}
