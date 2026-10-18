typedef void (*Callback)(void *argument);

extern unsigned char D_800EDF08[];

void func_80083540(unsigned int index, unsigned int amount) {
    register unsigned char *base asm("$3") = D_800EDF08;
    register unsigned int current asm("$2");
    unsigned char *entry;
    unsigned int limit;

    asm("" : "+r"(base));
    entry = (unsigned char *)(index * 20 + (unsigned int)base);
    current = *(unsigned int *)(entry + 0x08);
    limit = *(unsigned int *)(entry + 0x0C);
    asm("addu $5,$2,$5" : "+r"(amount) : "r"(current));
    *(unsigned int *)(entry + 0x08) = amount;
    if (amount >= limit) {
        Callback callback = *(Callback *)(entry + 0x10);

        *(unsigned int *)(entry + 0x08) = amount - limit;
        callback(*(void **)(entry + 0x04));
    }
}
