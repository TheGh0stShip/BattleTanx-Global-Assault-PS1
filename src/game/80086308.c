extern unsigned char D_800EE488[];

typedef void (*Callback)(int index, void *context, void *argument);

void func_80086308(int index, void *argument) {
    register unsigned char *base asm("$2") = D_800EE488;
    register unsigned char *entry asm("$3");
    register Callback callback asm("$2");

    asm("" : "+r"(base));
    entry = (unsigned char *)(index * 16);
    asm("addu $3,$3,$2" : "+r"(entry) : "r"(base));
    callback = *(Callback *)(entry + 0x14);

    if (callback != 0) {
        void *context = *(void **)(entry + 0x0C);

        *(Callback *)(entry + 0x14) = 0;
        callback(index, context, argument);
    }
}
