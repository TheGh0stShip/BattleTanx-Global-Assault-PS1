extern short D_800B6EB8[];

int func_8008ACC0(int a) {
    if (a < 0) {
        a = -a;
    }
    a &= 0xFFF;
    if (a <= 2048) {
        if (a <= 1024) {
            return D_800B6EB8[1024 - a];
        }
        return -D_800B6EB8[a - 1024];
    }
    if (a <= 3072) {
        return -D_800B6EB8[3072 - a];
    }
    return D_800B6EB8[a - 3072];
}
