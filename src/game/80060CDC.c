extern unsigned char D_800A8B18[];
extern unsigned short D_800AACDE;

struct DisplayState {
    unsigned char pad_000[0x3A8];
    unsigned int field_3A8;
    unsigned char pad_3AC[0x3C];
    unsigned int field_3E8;
};

extern struct DisplayState D_800A8B24;

void func_80057D24(unsigned char *text);

int func_80060CDC(void) {
    if (D_800AACDE != 0) {
        func_80057D24(D_800A8B18);
        D_800AACDE--;
    }

    D_800A8B24.field_3A8 = 0;
    D_800A8B24.field_3E8 = 0;
    return 0;
}
