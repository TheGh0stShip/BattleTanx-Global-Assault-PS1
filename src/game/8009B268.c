extern unsigned char *D_800B76F0_A;
extern unsigned char *D_800B76F0_B;

void func_8009B268(int enabled) {
    register unsigned char *state asm("$3");
    unsigned short value;

    if (enabled == 0) {
        asm("lui $3,%%hi(D_800B76F0_A)\n\tlw $3,%%lo(D_800B76F0_A)($3)"
            : "=r"(state));
        value = *(unsigned short *)(state + 0x1AA);
        value &= 0xFFFE;
    } else {
        asm("lui $3,%%hi(D_800B76F0_B)\n\tlw $3,%%lo(D_800B76F0_B)($3)"
            : "=r"(state));
        value = *(unsigned short *)(state + 0x1AA);
        value |= 1;
    }
    *(unsigned short *)(state + 0x1AA) = value;
}
