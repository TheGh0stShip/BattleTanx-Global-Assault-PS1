extern int *D_800B0D38;
extern volatile int *D_800B0D44;
extern volatile int *D_800B0D54;
extern int D_800B0D58;
extern volatile int D_800B0D5C;
extern int D_800B0D68;
extern int D_800EC394;
extern int D_800EC49C;

extern int func_800944F4(int);
extern void func_80081E64(void *, int, int);
extern int func_80081CA0(int);

int func_8008189C(int mode)
{
    D_800B0D68 = func_800944F4(0);
    D_800B0D5C = 0;
    D_800B0D58 = D_800B0D5C;
    switch (mode & 7) {
    case 0:
    case 5:
        *D_800B0D44 = 0x401;
        *D_800B0D54 |= 0x800;
        *D_800B0D38 = 0;
        func_80081E64(&D_800EC394, 0, 0x100);
        func_80081E64(&D_800EC49C, 0, 0x1800);
        break;
    case 1:
    case 3:
        *D_800B0D44 = 0x401;
        *D_800B0D54 |= 0x800;
        *D_800B0D38 = 0x02000000;
        *D_800B0D38 = 0x01000000;
        break;
    }
    func_800944F4(D_800B0D68);
    if ((mode & 7) == 0) {
        return func_80081CA0(mode);
    }
    return 0;
}
