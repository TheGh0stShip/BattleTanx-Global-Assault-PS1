void func_80081E64(unsigned char *destination, unsigned char value, int count) {
    while (count-- != 0) {
        *destination++ = value;
    }
}
