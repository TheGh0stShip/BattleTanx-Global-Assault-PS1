void func_80072F10(int *source, int unused1, int type, int unused2, int *destination) {
    if (type == 7) {
        destination[0] = source[4];
        destination[1] = source[5];
        destination[2] = source[6];
        destination[3] = 0;
        destination[4] = 0;
        destination[5] = 0;
    }
}
