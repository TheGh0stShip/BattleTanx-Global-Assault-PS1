extern short D_800A46F4[];
extern short D_800A4720[];
extern int D_800A474C;
extern int D_800A4750;

void func_8002A30C(void) {
    int i;

    D_800A474C = 0;
    D_800A46F4[5] = 1;
    for (i = 0; i < 21; i++) {
        D_800A46F4[i] = D_800A4720[i];
        D_800A474C += D_800A4720[i];
    }
    D_800A4750 = 1;
}
