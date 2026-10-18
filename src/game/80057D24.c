void func_80057D24(unsigned char *text) {
    unsigned char *start = text;

    while (*text != 0) {
        text++;
    }
    if (text != start) {
        text[-1] = 0;
    }
}
