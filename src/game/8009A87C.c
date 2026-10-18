extern unsigned short *D_800B76F0;
extern unsigned int D_800B7718;

void func_8009A87C(unsigned int index, unsigned int value, int shifted) {
    register unsigned char *destination asm("$2") =
        (unsigned char *)(index << 1);
    register unsigned int stored asm("$5") = value;

    if (shifted == 0) {
        register unsigned short *base asm("$3") = D_800B76F0;

        destination += (unsigned int)base;
        *(unsigned short *)destination = stored;
    } else {
        register unsigned short *base asm("$4");
        register unsigned int shift asm("$3");

        asm("lui $4,%%hi(D_800B76F0)\n\t"
            "lw $4,%%lo(D_800B76F0)($4)\n\t"
            "lui $3,%%hi(D_800B7718)\n\t"
            "lw $3,%%lo(D_800B7718)($3)"
            : "=r"(base), "=r"(shift));
        destination += (unsigned int)base;
        *(unsigned short *)destination = stored >> shift;
    }
    asm volatile("");
}
