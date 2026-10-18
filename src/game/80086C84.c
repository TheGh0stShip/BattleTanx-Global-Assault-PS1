void func_80086C84(void) {
    register volatile unsigned int *global_pointer asm("$28");
    unsigned int value = global_pointer[0x3C / 4];
    register unsigned int mixed asm("$3") = value >> 1;
    register unsigned int top_bit asm("$4");

    asm("" : "+r"(mixed));
    top_bit = value << 31;
    asm("" : "+r"(top_bit));
    mixed |= top_bit;
    mixed ^= value;
    global_pointer[0x3C / 4] = value - mixed;
}
