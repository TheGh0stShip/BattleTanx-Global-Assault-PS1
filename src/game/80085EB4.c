void *func_800855D0(void);

unsigned int func_80085EB4(unsigned char *arena) {
    register unsigned int result asm("$16") = 0;
    register unsigned int remaining asm("$6");
    register unsigned int mask asm("$7");
    register unsigned char *slot asm("$4");
    register unsigned char *entry asm("$5");
    unsigned char *root;

    asm("" : "+r"(result));
    if (arena == (unsigned char *)-1) {
        arena = func_800855D0();
    }
    root = *(unsigned char **)arena;
    if (root == 0) {
        return result;
    }

    remaining = 32;
    mask = ~1U;
    slot = root + 0x80;
    do {
        slot -= 4;
        entry = *(unsigned char **)(slot + 8);
        remaining--;
        while (entry != 0) {
            register unsigned int size asm("$3") =
                *(unsigned int *)(entry + 4);

            asm("" : "+r"(size));
            size &= mask;
            asm("" : "+r"(size));
            if (result < size) {
                result = size;
            }
            entry = *(unsigned char **)(entry + 12);
        }
        if (remaining == 0) {
            return result;
        }
    } while (result == 0);
    slot += 4;
    return result;
}
