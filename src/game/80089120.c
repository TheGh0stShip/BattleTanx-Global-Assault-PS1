struct StreamFlags {
    unsigned char pad_00[0x32];
    unsigned char active_32;
    unsigned char active_33;
    unsigned char pad_34[5];
    unsigned char stopping_39;
    unsigned char pad_3A[2];
    unsigned char pending_3C;
};

extern struct StreamFlags D_800EEAE8;

void func_80088FB0(void);

void func_80089120(void) {
    if (D_800EEAE8.active_33 == 0 ||
        D_800EEAE8.active_32 == 0 ||
        D_800EEAE8.stopping_39 != 0 ||
        D_800EEAE8.pending_3C != 0) {
        func_80088FB0();
    }
}
