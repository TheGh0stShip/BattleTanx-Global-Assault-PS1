struct StreamFinishState {
    unsigned char pad_00[0x24];
    unsigned int count_24;
    unsigned char pad_28[4];
    void *context_2C;
    unsigned char pad_30[3];
    unsigned char active_33;
    unsigned char pad_34[9];
    unsigned char value_3D;
    unsigned char pad_3E[0x2E];
    void *value_6C;
    unsigned int value_70;
    unsigned char pad_74[0x0C];
    void (*callback_80)(void *context, void *value, void *next, int selected);
    void *value_84;
    void *value_88;
};

extern struct StreamFinishState D_800EEAE8;

void func_80088DC8(unsigned int mode) {
    void *value;
    void *next;
    void (*callback)(void *, void *, void *, int);

    mode &= 0xFF;
    if (mode != 2) {
        D_800EEAE8.count_24++;
    }
    value = D_800EEAE8.value_6C;
    callback = D_800EEAE8.callback_80;
    next = D_800EEAE8.value_84;
    D_800EEAE8.value_6C = 0;
    D_800EEAE8.value_70 = 0;
    D_800EEAE8.callback_80 = 0;
    D_800EEAE8.active_33 = 1;
    D_800EEAE8.value_3D = 0;
    D_800EEAE8.value_88 = next;
    if (callback != 0) {
        callback(D_800EEAE8.context_2C, value, next, mode == 2);
    }
}
