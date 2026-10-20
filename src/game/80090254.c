extern unsigned int D_800B7718;
extern int *D_800B7BD8;
extern int D_800B7BD4;
extern int D_800B7BD0;

int func_80090254(int count, int *output) {
    register int result asm("$2") = count;
    register unsigned int shift asm("$4");
    register unsigned int header asm("$3");
    register int *out asm("$5") = output;

    asm("" : "+r"(out));
    if (result > 0) {
        goto active;
    }
    result = 0;
    goto done;
active:
    header = 0x40000000U;
    shift = D_800B7718;
    header |= 0x1010;
    out[0] = header;
    header = 0x10000U;
    asm("" : "+r"(header));
    asm volatile("lui $1,%%hi(D_800B7BD8)\n\t"
                 "sw %0,%%lo(D_800B7BD8)($1)"
                 : : "r"(out) : "$1", "memory");
    asm volatile("lui $1,%%hi(D_800B7BD4)\n\t"
                 "sw $0,%%lo(D_800B7BD4)($1)"
                 : : : "$1", "memory");
    asm volatile("lui $1,%%hi(D_800B7BD0)\n\t"
                 "sw %0,%%lo(D_800B7BD0)($1)"
                 : : "r"(result) : "$1", "memory");
    out[1] = (header << shift) - 0x1010;
done:
    asm("" : "+r"(result));
    return result;
}
