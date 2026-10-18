extern int D_800A4B20;
extern unsigned char D_800DE068;
extern int D_800DE0C8;
extern void func_80083194(void *value);
extern void func_800826A0(void *value);
extern void func_80068F9C(int value);

void func_8003DEF8(void) {
    D_800A4B20 -= 1;
    func_80083194(&D_800DE068);
    func_800826A0(&D_800DE068);
    func_80068F9C(D_800DE0C8);
}
