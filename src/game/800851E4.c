extern unsigned char D_800EE028[];

void func_800851E4(unsigned int index, unsigned int flags,
                   unsigned short first, unsigned short second) {
    register unsigned int counter asm("$9") = 0;
    register unsigned int mask asm("$8") = 1;
    register unsigned char *base asm("$10");
    register unsigned int temporary asm("$2");
    register unsigned int offset asm("$3");

    asm("" : "+r"(counter));
    asm("" : "+r"(mask));
    asm volatile(
        "lui $2, %%hi(D_800EE028)\n\t"
        "addiu %0, $2, %%lo(D_800EE028)"
        : "=r"(base)
        :
        : "$2");
    temporary = index << 3;
    asm("" : "+r"(temporary));
    temporary += index;
    asm("" : "+r"(temporary));
    temporary <<= 2;
    asm("" : "+r"(temporary));
    temporary -= index;
    asm("" : "+r"(temporary));
    offset = temporary << 2;
    asm("" : "+r"(offset));
    do {
        if (flags & mask) {
            unsigned char *entry = (unsigned char *)(offset + (unsigned int)base);

            *(unsigned short *)(entry + 0x2A) = first;
            *(unsigned short *)(entry + 0x4A) = first;
            *(unsigned short *)(entry + 0x6A) = second;
        }
        offset += 2;
        counter++;
        mask <<= 1;
    } while (counter < 16);
}
