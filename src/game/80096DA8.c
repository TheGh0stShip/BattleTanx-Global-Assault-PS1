extern int D_800EF070;
extern int D_800EF074;
extern int D_800EF078;
extern int D_800EF07C;

int func_80096DA8(void) {
    register int scaled asm("$2");
    register int total asm("$4");
    register int second asm("$3");

    scaled = D_800EF074;
    asm volatile("" : "+r"(scaled) : : "memory");
    asm volatile(
        "lui $4,%%hi(D_800EF070)\n\t"
        "lw $4,%%lo(D_800EF070)($4)"
        : "=r"(total)
        :
        : "memory"
    );
    second = D_800EF078;
    asm volatile("" : "+r"(second) : : "memory");
    scaled *= 2;
    total += scaled;
    second *= 4;
    scaled = D_800EF07C;
    total += second;
    scaled *= 8;
    return total + scaled;
}
