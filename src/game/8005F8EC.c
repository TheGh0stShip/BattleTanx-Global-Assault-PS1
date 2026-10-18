typedef signed int s32;
typedef unsigned short u16;

extern u16 D_800AACE6;
extern u16 D_800E4994;
extern void func_80059A80(void);

s32 func_8005F8EC(void) {
    if (D_800AACE6 != 0)
        return 0;
    D_800E4994 = 1;
    func_80059A80();
    return 1;
}
