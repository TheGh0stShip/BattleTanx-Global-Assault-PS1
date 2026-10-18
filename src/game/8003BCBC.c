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
        ".set noat\n\t"
        "div $0,$3,$2\n\t"
        "bne $2,$zero,1f\n\t"
        "nop\n\t"
        "break 7,0\n"
        "1:\n\t"
        "addiu $1,$0,-1\n\t"
        "bne $2,$1,2f\n\t"
        "lui $1,0x8000\n\t"
        "bne $3,$1,2f\n\t"
        "nop\n\t"
        "break 6,0\n"
        "2:\n\t"
        "mflo %0\n\t"
        ".set at"
        : "+r"(scale)
        : "r"(delta)
        : "$1"
    );

    D_800DDFF8.value = value;
    D_800DDFF8.start = start;
    D_800DDFF8.end = end;
    D_800DDFF8.scale = scale;
}
