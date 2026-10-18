struct StreamControl {
    unsigned char pad_00[0x42];
    unsigned char requested;
};

extern struct StreamControl D_800EEAE8;

int func_80089098(int value);
void func_80088D50(unsigned int mode);
void func_80089294(void);

void func_80089188(unsigned int mode) {
    int ready = 1;
    register struct StreamControl *control asm("$2") = &D_800EEAE8;

    asm("" : "+r"(control));
    mode &= 0xFF;
    control->requested = 1;
    if (mode != 2) {
        ready = func_80089098(0) == 0;
    }
    if (ready) {
        func_80088D50(mode);
    } else {
        func_80089294();
    }
}
