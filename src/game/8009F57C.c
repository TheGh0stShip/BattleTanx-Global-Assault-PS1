void func_8009F57C(unsigned char *packet) {
    packet[0x36] = 0x4B;
    *(void **)(packet + 0x2C) = 0;
    packet[0x35] = 0;
}
