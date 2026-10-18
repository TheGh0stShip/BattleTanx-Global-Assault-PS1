typedef void (*Callback)(void *value);

extern unsigned char D_800EDC9C[];

void func_80082B9C(unsigned int index) {
    register unsigned char *table asm("$2") = D_800EDC9C;
    register unsigned char *entry asm("$4");
    register void *value asm("$3");

    asm("" : "+r"(table));
    index *= 4;
    asm("addu $4,$4,$2" : "=r"(entry) : "r"(index), "r"(table));
    value = *(void **)(entry + 0x1C8);

    *(void **)(entry + 0x1C8) = 0;
    if (value != 0) {
        register Callback callback asm("$2") = *(Callback *)(entry + 0x1F0);

        *(Callback *)(entry + 0x1F0) = 0;
        if (callback != 0) {
            callback(value);
        }
    }
}
