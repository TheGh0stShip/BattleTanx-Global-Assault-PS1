extern int func_8009AED4(int);
extern int D_800B7760;
extern int D_800B7724;
extern int D_800B7758;

int func_80090D60(int mode) {
    int r;

    if (D_800B7760 == 1 || D_800B7724 == 1) {
        return 1;
    }
    r = func_8009AED4(D_800B7758);
    if (mode == 1) {
        if (r == 0) {
            do {
                r = func_8009AED4(D_800B7758);
            } while (r == 0);
        }
        r = 1;
    } else if (r != 1) {
        return r;
    }
    D_800B7724 = r;
    return r;
}
