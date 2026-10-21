typedef signed char s8;
typedef signed int s32;
typedef unsigned char u8;

extern u8 D_800B6B31[];
extern s32 D_800B8D0C;
extern s32 D_800B8D10;
extern u8 D_800EFCB8[];
extern void func_8009F74C(s32, u8 *, s32);

void func_8009F89C(s8 value) {
    if (value != 9) {
        if (value == 10) {
            func_8009F89C(13);
            D_800B8D0C = 0;
        } else if (D_800B6B31[(u8)value] & 0x97) {
            D_800B8D0C++;
        }
        if (D_800B8D10 >= 0x20) {
            func_8009F74C(1, D_800EFCB8, D_800B8D10);
            D_800B8D10 = 0;
        }
        D_800EFCB8[D_800B8D10] = (u8)value;
        D_800B8D10++;
    } else {
        do {
            func_8009F89C(0x20);
        } while (D_800B8D0C & 7);
    }
}
