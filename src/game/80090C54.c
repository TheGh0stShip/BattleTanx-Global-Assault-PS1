typedef struct Entry {
    unsigned char pad[12];
    unsigned short state;
    unsigned char tail[2];
} Entry;

extern Entry * volatile D_800B76F0;
extern unsigned int volatile D_800B775C;

void func_80090C54(unsigned char *output) {
    register int limit asm("$10") = 24;
    register int index asm("$6") = 0;
    register unsigned int one asm("$7") = 1;
    register unsigned int three asm("$9") = 3;
    register unsigned int two asm("$8") = 2;
    register unsigned char *current asm("$5") = output;

    do {
        register unsigned int offset asm("$4") = index << 4;
        register Entry *base asm("$2");
        register unsigned int selected asm("$3");
        register unsigned int state asm("$2");
        asm volatile("lui %0,%%hi(D_800B76F0)\n\t"
                     "lw %0,%%lo(D_800B76F0)(%0)"
                     : "=r"(base) : : "memory");
        asm volatile("lui %0,%%hi(D_800B775C)\n\t"
                     "lw %0,%%lo(D_800B775C)(%0)"
                     : "=r"(selected) : : "memory");
        offset += (unsigned int)base;
        state = one << index;
        selected &= state;
        state = ((Entry *)offset)->state;
        if (selected != 0) {
            if (state != 0) {
                *current = one;
            } else {
                *current = three;
            }
        } else if (state != 0) {
            *current = two;
        } else {
            *current = 0;
        }
        index++;
        current++;
    } while (index < limit);
}
