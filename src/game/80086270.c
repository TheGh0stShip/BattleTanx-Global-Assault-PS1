extern unsigned int D_800EE488;

void func_80086270(int index, int enabled) {
    register int bit asm("$6");
    register int sentinel asm("$2");

    if (enabled == 0) {
        bit = index;
        goto clear;
    }
    bit = index;
    sentinel = -1;
    asm("" : "+r"(sentinel));
    if (bit == sentinel) {
        D_800EE488 = bit;
        return;
    }
    D_800EE488 |= 1U << bit;
    return;

clear:
    sentinel = -1;
    asm("" : "+r"(sentinel));
    if (bit == sentinel) {
        D_800EE488 = 0;
        return;
    }
    D_800EE488 &= ~(1U << bit);
}
