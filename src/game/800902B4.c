void func_800902B4(int value) {
    register int enabled asm("$2");
    register unsigned char *destination asm("$1");

    if (value == 0) {
        enabled = 1;
        goto zero;
    }
    enabled = 1;
    asm("" : "+r"(enabled));
    if (value != enabled) {
        enabled = 0;
        goto store;
    }
    enabled = 0;
    asm("" : "+r"(enabled));
    enabled = 1;
    goto store;

zero:
    enabled = 0;
store:
    asm("");
    destination = (unsigned char *)0x800B0000;
    asm("" : "+r"(destination));
    *(int *)(destination + 0x7760) = value;
    destination = (unsigned char *)0x800B0000;
    asm("" : "+r"(destination));
    *(int *)(destination + 0x770C) = enabled;
}
