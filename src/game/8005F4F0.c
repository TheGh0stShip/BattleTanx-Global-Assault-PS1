extern int D_800C60C0;
extern unsigned char D_800BFB70;
extern unsigned char D_800AEA46;
extern int D_800EAFBC;
extern void func_8007646C(void);
extern void func_8006AB60(int value);
extern void func_80076060(void *value, int count);
extern void func_80076184(void);
extern void func_80075AEC(void);
extern void func_8007586C(int value);

int func_8005F4F0(void) {
    if (D_800C60C0 & 1) {
        func_8007646C();
        func_8006AB60(15);
        D_800AEA46 = 100;
        func_80076060(&D_800BFB70, 1);
        func_80076184();
        func_80075AEC();
        D_800EAFBC = 5;
        func_8007586C(5);
    }
    return 0;
}
