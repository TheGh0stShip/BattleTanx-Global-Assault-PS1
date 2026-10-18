extern int D_800EF080;
extern int D_800EF084;
extern int D_800EF088;
extern int D_800EF08C;

int func_80096DE4(void) {
    register int scaled asm("$2");
    register int total asm("$4");
    register int second asm("$3");

    scaled = D_800EF084;
    asm volatile("" : "+r"(scaled) : : "memory");
    asm volatile(
        "lui $4,%%hi(D_800EF080)\n\t"
        "lw $4,%%lo(D_800EF080)($4)"
        : "=r"(total)
        :
        : "memory"
    );
    second = D_800EF088;
    asm volatile("" : "+r"(second) : : "memory");
    scaled *= 2;
    total += scaled;
    second *= 4;
    scaled = D_800EF08C;
    total += second;
    scaled *= 8;
    return total + scaled;
}
