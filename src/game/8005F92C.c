extern unsigned char D_800A6B48;
extern int D_800EAFBC;
extern void func_8003DEF8(void);
extern void func_80075AEC(void);
extern void func_80059A80(void *value);
extern void func_80059550(void *source, void *value, int count);

int func_8005F92C(void *value) {
    func_8003DEF8();
    func_80075AEC();
    func_80059A80(value);
    func_80059550(&D_800A6B48, value, 1);
    D_800EAFBC = 6;
    return 1;
}
