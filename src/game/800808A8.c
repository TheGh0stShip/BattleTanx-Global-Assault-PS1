unsigned int func_800808A8(int enabled, int mode, unsigned int value) {
    register unsigned int command asm("$3") = 0xE1000000;
    register unsigned int result asm("$2");

    if (mode != 0) {
        command |= 0x200;
    }
    result = value & 0x9FF;
    if (enabled != 0) {
        result |= 0x400;
    }
    return command | result;
}
