extern unsigned char D_800EE488[];
extern void func_80086308(int index, void *argument);
extern void func_8008523C(int index, unsigned int first, unsigned int second);

typedef void (*Callback)(int index, void *context, void *argument);

void func_8008634C(int index, unsigned char *context, Callback callback) {
    register unsigned char *base asm("$18") = D_800EE488;
    register unsigned int bit asm("$3") = 1;
    register unsigned int active asm("$2");

    asm("" : "+r"(base));
    active = *(volatile unsigned int *)D_800EE488;
    bit <<= index;
    active &= bit;
    if (active) {
        register unsigned char *entry asm("$2");

        func_80086308(index, 0);
        entry = (unsigned char *)(index * 16);
        asm("addu $2,$2,$18" : "+r"(entry) : "r"(base));
        *(unsigned int *)(entry + 0x08) = 0;
        *(unsigned char **)(entry + 0x0C) = context;
        *(unsigned char **)(entry + 0x10) = context;
        *(Callback *)(entry + 0x14) = callback;
        func_8008523C(index, context[0], context[1]);
    }
}
