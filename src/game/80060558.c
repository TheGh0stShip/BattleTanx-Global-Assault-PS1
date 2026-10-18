typedef unsigned char u8;

extern u8 D_800A6188;
extern u8 D_800A6189;
extern void func_8005A648(void);

int func_80060558(void) {
    D_800A6188 = 0;
    D_800A6189 = 0;
    func_8005A648();
    return 1;
}
