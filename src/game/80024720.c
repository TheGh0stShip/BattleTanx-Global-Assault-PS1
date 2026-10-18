extern unsigned char *D_800D2FE4;

void func_80024720(unsigned char *indices, unsigned int *source,
                   unsigned short value) {
    register unsigned char *globals asm("$7") = (unsigned char *)0x800D0000;
    register unsigned int first asm("$3") = indices[1];
    register unsigned int second asm("$4") = indices[2];
    register unsigned int offset asm("$2");
    unsigned char *entry;

    asm("" : "+r"(globals), "+r"(first), "+r"(second));
    offset = first * 60;
    asm("" : "+r"(offset), "+r"(globals), "+r"(second));
    entry = *(unsigned char **)(globals + 0x2FE4);
    asm("" : "+r"(entry), "+r"(offset));
    offset += 0x24;
    entry += offset;
    entry += second * 12;
    *(unsigned int *)(entry + 0) = source[0];
    *(unsigned int *)(entry + 4) = source[2];
    *(unsigned short *)(entry + 8) = value;
}
