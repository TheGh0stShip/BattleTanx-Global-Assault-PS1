extern unsigned short *D_800B6B08;

int func_800944F4(unsigned short value) {
    register unsigned short *current asm("$3");
    int previous;

    asm("lui $3,%%hi(D_800B6B08)\n\tlw $3,%%lo(D_800B6B08)($3)" : "=r"(current));
    previous = *current;
    *current = value;
    return previous;
}
