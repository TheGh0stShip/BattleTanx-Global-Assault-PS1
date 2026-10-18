struct StreamCallbackState {
    unsigned char pad_00[0x2C];
    void *context;
    unsigned char pad_30[2];
    unsigned char active_32;
    unsigned char pad_33[13];
    unsigned char value_40;
    unsigned char pad_41;
    unsigned char value_42;
    unsigned char pad_43;
    unsigned int value_44;
    unsigned char pad_48[0x20];
    void (*callback_68)(void *context, int selected);
};

extern struct StreamCallbackState D_800EEAE8;

void func_80091604(int value);

void func_80088D50(unsigned int mode) {
    void (*callback)(void *, int) = D_800EEAE8.callback_68;

    D_800EEAE8.callback_68 = 0;
    func_80091604(0);
    D_800EEAE8.value_44 = 0;
    D_800EEAE8.value_40 = 0;
    D_800EEAE8.value_42 = 0;
    D_800EEAE8.active_32 = 1;
    asm("" ::: "memory");
    if (callback != 0) {
        callback(D_800EEAE8.context, (unsigned char)mode == 2);
    }
}
