typedef void (*DetachCallback)(void *value);

extern unsigned char D_800EDC9C;

void func_80082F7C(int slot, int unused, int adjustment, int keep_adjustment)
{
    register unsigned char *base asm("$2");
    register unsigned char *entry asm("$4");
    register void *value asm("$3");
    register DetachCallback callback asm("$8");

    base = &D_800EDC9C;
    asm("" : "+r"(base));
    entry = (unsigned char *)(slot << 2);
    entry += (int)base;
    value = *(void **)(entry + 0x1C8);

    *(void **)(entry + 0x1C8) = 0;
    if (value != 0) {
        callback = *(DetachCallback *)(entry + 0x240);
        *(DetachCallback *)(entry + 0x240) = 0;
        if (keep_adjustment == 0) {
            adjustment = 0;
        }
        *(int *)((unsigned char *)value + 0x10) += adjustment;
        if (callback != 0) {
            callback(value);
        }
    }
}
