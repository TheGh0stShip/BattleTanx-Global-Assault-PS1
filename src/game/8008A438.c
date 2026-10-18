void *func_8008A438(unsigned int size) {
    register unsigned char *global_pointer asm("$28");
    unsigned char *current;
    unsigned char *next;
    unsigned char *limit;
    register void *result asm("$6") = 0;

    size = ((size + 3) >> 2) << 2;
    current = *(unsigned char **)(global_pointer + 0x40);
    limit = *(unsigned char **)(global_pointer + 0x44);
    next = current + size;
    if (limit >= next) {
        result = current;
        *(unsigned char **)(global_pointer + 0x40) = next;
    }
    return result;
}
