typedef unsigned char u8;
typedef unsigned short u16;

void *func_8004A794(u16 index) {
    register unsigned int offset asm("$2");
    register u8 *base asm("$3");

    if (index == 0) {
        asm("");
        return 0;
    }
    base = (u8 *)0x800A0000;
    asm("" : "+r"(base));
    offset = index << 3;
    asm("" : "+r"(offset));
    offset -= index;
    asm("" : "+r"(offset));
    offset <<= 2;
    asm("" : "+r"(offset));
    base = *(u8 **)(base + 0x5B24);
    offset += 8;
    return base + offset;
}
