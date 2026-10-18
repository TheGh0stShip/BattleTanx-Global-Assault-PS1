void *func_8008A46C(unsigned int size) {
    register unsigned char *volatile *global_pointer asm("$28");
    unsigned char *result;

    size = ((size + 3) >> 2) << 2;
    result = global_pointer[0x40 / 4] - size;
    global_pointer[0x40 / 4] = result;
    return result;
}
