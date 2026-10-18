extern unsigned char D_800EE588[];

void func_8008AA48(void *destination, int value, unsigned int size);

void func_80086DD8(void) {
    unsigned int fill;
    int index;
    unsigned int *cursor;
    register unsigned char *reset asm("$2");
    register int enabled asm("$3");

    func_8008AA48(D_800EE588, 0, 0x560);
    fill = 0xFFFF0000;
    index = 7;
    cursor = (unsigned int *)(D_800EE588 + 28);
    do {
        cursor[3] = fill;
        index--;
        cursor--;
    } while (index >= 0);
    reset = D_800EE588;
    asm("" : "+r"(reset));
    enabled = 1;
    reset[8] = enabled;
}
