typedef struct SlotState {
    unsigned char unused0[12];
    unsigned short value;
    unsigned char unusedE[2];
} SlotState;

extern SlotState *D_800B76F0;
extern unsigned int D_800B775C;

int func_800901C4(unsigned int mask) {
    register unsigned int input asm("$4") = mask;
    register int index asm("$5");
    register unsigned int one asm("$6");
    register int cursor asm("$3");
    register unsigned int bit asm("$2");
    register SlotState *base asm("$2");
    register unsigned int active asm("$3");
    register unsigned char *slot asm("$4");
    register int result asm("$2");

    asm volatile(".set\tnoreorder\n\t"
                 "addiu %1,$0,-1\n\t"
                 "addu %3,$0,$0\n\t"
                 "addiu %2,$0,1\n\t"
                 "sllv %4,%2,%3\n"
                 "1:\n\t"
                 "and %4,%0,%4\n\t"
                 "bnez %4,3f\n\t"
                 "nop\n\t"
                 "addiu %3,%3,1\n\t"
                 "slti %4,%3,24\n\t"
                 "bnez %4,1b\n\t"
                 "sllv %4,%2,%3\n"
                 "2:\n\t"
                 "addiu %4,$0,-1\n\t"
                 "bne %1,%4,4f\n\t"
                 "sll %0,%1,4\n\t"
                 "j .L800901C4_done\n\t"
                 "nop\n"
                 "3:\n\t"
                 "j 2b\n\t"
                 "addu %1,%3,$0\n"
                 "4:\n\t"
                 ".set\treorder"
                 : "+r"(input), "=r"(index), "=r"(one),
                   "=r"(cursor), "=r"(bit));
    slot = (unsigned char *)input;
    base = D_800B76F0;
    asm volatile("" : "+r"(base));
    active = D_800B775C;
    asm volatile("" : "+r"(active));
    slot += (unsigned int)base;
    bit = 1U << index;
    active &= bit;
    asm volatile("" : "+r"(active) : : "memory");
    input = *(unsigned short *)(slot + 12);
    result = input != 0;
    if (active == 0) {
        result <<= 1;
        goto done;
    }
    result = 1;
    if (input != 0) {
        goto done;
    }
    result = 3;
done:
    asm volatile(".L800901C4_done:" : "+r"(result));
    return result;
}
