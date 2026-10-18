extern short D_800EC0AC[][19];
extern short D_800AEB3C[][19];
extern int D_800EC0F8[];

static inline void load_preset_row(unsigned char slot, int preset) {
    int i;

    for (i = 0; i < 19; i++) {
        D_800EC0AC[slot][i] = D_800AEB3C[preset][i];
    }
}

void func_8007A154(void) {
    unsigned char slot;
    int one;

    for (slot = 0, one = 1; slot < 2; slot++) {
        D_800EC0F8[slot] = one;
        load_preset_row(slot, 1);
    }
}
