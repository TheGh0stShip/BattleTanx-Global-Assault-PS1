void func_80097FE4(const unsigned char *source, unsigned char *destination) {
    unsigned int index = 0;
    unsigned char value = source[0];
    while (value != 0 && value != ';') {
        destination[index++] = value;
        value = source[index];
    }
    destination[index] = 0;
}
