extern int D_800A6084[4];
extern int D_800A60A4[4];

int func_8005E2EC(void) {
    int counts[5];
    int distinct;
    int i;

    distinct = 0;
    for (i = 4; i >= 0; i--) {
        counts[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (counts[D_800A6084[i]] == 0 && D_800A6084[i] != 0) {
            distinct++;
        }
        counts[D_800A6084[i]]++;
        if (D_800A60A4[i] == 2 && D_800A6084[i] == 0) {
            return 1;
        }
    }
    return distinct < 2;
}
