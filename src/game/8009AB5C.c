extern int D_800B7BC0;
extern int D_800B7758;
extern void func_80094198(void);
extern void func_800A2F60(void (*callback)(void));
extern int func_80094158(unsigned int desc, int spec, int mode, void *func);
extern int func_800940B4(int event);
extern void func_80094168(void);
extern void func_8009A4BC(void);

void func_8009AB5C(void)
{
    if (D_800B7BC0 == 0) {
        D_800B7BC0 = 1;
        func_80094198();
        func_800A2F60(func_8009A4BC);
        D_800B7758 = func_80094158(0xF0000009, 0x20, 0x2000, 0);
        func_800940B4(D_800B7758);
        func_80094168();
    }
}
