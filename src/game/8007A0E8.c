extern short D_800EC0AC[][19];
extern short D_800AEB3C[][19];

void func_8007A0E8(unsigned char slot, int preset) {
    int i;

    for (i = 0; i < 19; i++) {
        D_800EC0AC[slot][i] = D_800AEB3C[preset][i];
    }
}
