void func_80039010(int *source, int unused1, int type, int unused2, int *destination) {
    if (type == 7) {
        destination[0] = source[2];
        destination[1] = source[3];
        destination[2] = source[4];
        destination[3] = source[5];
        destination[4] = 0;
        destination[5] = source[6];
    }
}
