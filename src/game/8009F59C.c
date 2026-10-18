void func_8009F59C(void) {
    register int value asm("$2") = -1;
    register int *base asm("$1") = (int *)0x800C0000;

    asm("" : "+r"(value), "+r"(base));
    base[-0x7314 / 4] = value;
}
