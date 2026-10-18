extern unsigned char D_800D2FEC;
extern unsigned char D_800E3E68;

int func_80022994(void)
{
    register int offset asm("$4") = D_800D2FEC;

    if (offset != 0) {
        register int limit asm("$5") = offset;
        register int index asm("$3") = 0;
        register int sentinel asm("$8") = 127;
        register unsigned char *base asm("$7");
        register int expected asm("$6");
        unsigned char *object;
        int state;

        __asm__(
            "lui $2,%%hi(D_800E3E68)\n\t"
            "addiu %0,$2,%%lo(D_800E3E68)"
            : "=r"(base)
        );
        expected = 1;
        offset = 0;
        do {
            if (index == sentinel) {
                object = 0;
            } else {
                object = (unsigned char *)(offset + (int)base);
            }
            state = *(int *)(object + 0x58);
            if (state == expected) {
                return 1;
            }
            index++;
            offset += 0x114;
        } while (index < limit);
    }
    return 0;
}
