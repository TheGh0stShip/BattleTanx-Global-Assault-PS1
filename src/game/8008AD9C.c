extern short D_800B6EB8[];

int func_8008AD9C(int a) {
    if (a <= 2048) {
        if (a <= 1024) {
            return D_800B6EB8[a];
        }
        return D_800B6EB8[2048 - a];
    }
    if (a <= 3072) {
        return -D_800B6EB8[a - 2048];
    }
    return -D_800B6EB8[4096 - a];
}
