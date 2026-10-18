extern void *D_800A4B20;
extern unsigned char D_800AE9EA;
extern char D_800DE068;
extern char D_800BEB2C;
extern void *D_800DE0C8;

void func_8007646C(void);
void func_80082424(void *, void *);
void *func_80068F34(int);

void func_8003DFC8(void) {
    if (D_800A4B20 == 0) {
        if (D_800AE9EA != 0) {
            func_8007646C();
        }
        func_80082424(&D_800DE068, &D_800BEB2C);
        D_800DE0C8 = func_80068F34(0x70830);
    }
}
