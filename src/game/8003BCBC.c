typedef struct RangeState {
    unsigned int unknown[4];
    unsigned int value;
    unsigned int start;
    unsigned int end;
    int scale;
} RangeState;

extern RangeState D_800DDFF8;

void func_8003BCBC(int start, int end,
                   unsigned int value) {
    register int delta asm("$2") = end - start;
    register int scale asm("$3") = 0x1000000;

    asm("" : "+r"(delta), "+r"(scale));
    asm volatile(
        ".set noreorder\n\t"
        ".set nomacro\n\t"
        ".word 0x0062001A\n\t"
        ".word 0x14400002\n\t"
        "nop\n\t"
        ".word 0x0007000D\n"
        "addiu $1,$0,-1\n\t"
        ".word 0x14410004\n\t"
        "lui $1,0x8000\n\t"
        ".word 0x14610002\n\t"
        "nop\n\t"
        ".word 0x0006000D\n"
        "mflo %0"
        : "+r"(scale)
        : "r"(delta)
        : "$1"
    );

    D_800DDFF8.value = value;
    D_800DDFF8.start = start;
    D_800DDFF8.end = end;
    D_800DDFF8.scale = scale;
}
