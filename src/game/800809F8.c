unsigned int func_800809F8(unsigned int first, unsigned int second) {
    return 0xE5000000 | ((second & 0x7FF) << 11) | (first & 0x7FF);
}
