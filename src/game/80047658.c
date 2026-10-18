int func_80047658(const unsigned char *object) {
    register unsigned int flags asm("$3");
    register int result asm("$2");

    if (object == 0) {
        result = 0;
        goto done;
    }
    flags = *(const unsigned int *)(object + 0x218);
    asm("" : "+r"(flags));
    result = flags & 1;
    asm("" : "+r"(result));
    if (result == 0) {
        goto zero;
    }
    flags &= 8;
    asm("" : "+r"(flags));
    result = 1;
    if (flags == 0) {
        goto done;
    }
zero:
    result = 0;
done:
    return result;
}
