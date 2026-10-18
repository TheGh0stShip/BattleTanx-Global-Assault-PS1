extern unsigned char D_800A6080;
extern unsigned char D_800A6081;
extern unsigned char D_800E4834;
extern unsigned char D_800E4830;
extern unsigned char D_800AACE5;
extern unsigned char D_800AACE4;
extern unsigned char D_800E482C;
extern unsigned char D_800E483C;
extern unsigned char D_800E4824;
extern int D_800EC0F8[];
extern int D_800A9570;
extern int D_800A9838;
extern int func_800851D4(void);
extern int func_800862D4(int);
extern void func_80059550(void *, void *, int);

int func_8005F588(void *menu) {
    D_800E4834 = D_800A6080;
    D_800E4830 = D_800A6081;
    if (func_800851D4() & 1) {
        if (func_800851D4() & 2) {
            D_800AACE5 = 2;
            func_80059550(&D_800A9570, menu, 1);
        } else {
            D_800AACE5 = 1;
            D_800AACE4 = 0;
            D_800E482C = 0;
            D_800E483C = D_800EC0F8[0];
            if (func_800862D4(0)) {
                D_800E4824 = 1;
            } else {
                D_800E4824 = 0;
            }
            func_80059550(&D_800A9838, menu, 1);
        }
    }
    return 1;
}
