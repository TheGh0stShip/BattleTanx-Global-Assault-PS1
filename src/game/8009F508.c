void func_8009F508(unsigned char *packet) {
    packet[0x36] = 0x45;
    *(void **)(packet + 0x2C) = 0;
    packet[0x35] = 0;
}
