typedef unsigned char u8;
typedef unsigned short u16;

extern u8 D_800AACD6;
extern u8 D_800AACD7;
extern u8 D_800AACD8;
extern u8 D_800AACD9;
extern u8 D_800AACDA;
extern u16 D_800E4994;

int func_8005F9C0(void) {
    if (D_800AACD6 != 0 || (D_800AACD7 != 0 && D_800AACD8 != 0)) {
        D_800AACD9 = 0;
        D_800AACDA = 0;
        D_800E4994 = 1;
        return 1;
    }
    return 0;
}
