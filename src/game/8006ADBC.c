typedef unsigned int u32;

extern u32 func_80086C84(void);
extern int func_8009383C(void *entry, int arg1, int arg2, int variant,
                        int arg4, void (*callback)(void *));
extern char D_800ADE3C[];

void func_8006ADBC(void *context) {
    char *base;
    void **entry;

    if (context != 0) {
        base = D_800ADE3C;
        entry = (void **)(base + ((func_80086C84() >> 14) & 4));
        func_8009383C(*entry, 0, 0, (func_80086C84() >> 16) & 7,
                      0, func_8006ADBC);
    }
}
