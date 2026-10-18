void func_8009F53C(unsigned char *packet, unsigned char value) {
    packet[0x36] = 0x46;
    *(void **)(packet + 0x2C) = packet + 0x24;
    packet[0x24] = value;
    packet[0x35] = 1;
}
