unsigned int func_800A1920(const unsigned char *packet) {
    unsigned int index = 0;
    register unsigned int sum asm("$5") = 0;
    unsigned int count = packet[0] + 3;

    asm("" : "+r"(sum));

    for (; index < count; index++) {
        sum += packet[index];
    }
    return sum & 0xFF;
}
