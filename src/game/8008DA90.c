unsigned short func_8008DA90(int first, unsigned int second) {
    return (second << 6) | ((first >> 4) & 0x3F);
}
