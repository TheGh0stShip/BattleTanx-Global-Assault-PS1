extern unsigned short D_800A60D8;
extern int D_800A6070;
extern unsigned char D_800A6C88;
extern unsigned char D_800A7770;

extern void func_80059550(void *descriptor, void *object, int value);
extern void func_8005A648(void *object);

int func_80060024(void *object) {
    if (D_800A60D8 != 0 && D_800A6070 == 1)
        func_80059550(&D_800A7770, object, 1);
    else
        func_80059550(&D_800A6C88, object, 1);
    func_8005A648(object);
    func_8005A648(&D_800A6C88);
    return 0;
}
