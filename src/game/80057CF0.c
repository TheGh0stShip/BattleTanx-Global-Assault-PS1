void func_80057CF0(unsigned char *text, unsigned char value) {
    while (*text != 0) {
        text++;
    }
    text[0] = value;
    text[1] = 0;
}
