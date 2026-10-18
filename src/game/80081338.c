extern volatile unsigned int *D_800B0D38;
extern unsigned int *D_800B0D34;

unsigned int func_80081338(unsigned int value) {
    register unsigned int mask asm("$2") = 0x10000000;
    register volatile unsigned int *target asm("$3") = D_800B0D38;
    register unsigned int command asm("$4") = value;

    asm("" : "+r"(mask), "+r"(target), "+r"(command));
    command |= mask;
    asm("" : "+r"(command));
    *target = command;
    asm("" : : : "memory");
    return *D_800B0D34 & 0x00FFFFFF;
}
