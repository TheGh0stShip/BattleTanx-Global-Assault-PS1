void func_800A3A24(int value) {
    register unsigned int counter asm("$2") = 0x1F801120;
    register int *first asm("$1");

    asm("lhu $2,0($2)" : "+r"(counter));
    first = (int *)0x800F0000;
    asm("" : "+r"(first));
    first[-0x1C4 / 4] = value;
    asm("" : : : "memory");
    {
        register int *second asm("$1") = (int *)0x800F0000;
        asm("" : "+r"(second));
        second[-0x1C0 / 4] = counter;
    }
}
