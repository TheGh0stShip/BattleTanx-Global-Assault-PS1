extern unsigned short D_800A60D8;
extern int D_800A6070;
extern unsigned char D_800A6F28;
extern unsigned char D_800A7A50;
extern void func_80059550(void *, void *, int);
extern void func_8005A648(void *);

int func_80060114(void *object) {
    if (D_800A60D8 != 0 && D_800A6070 == 1)
        func_80059550(&D_800A7A50, object, 1);
    else
        func_80059550(&D_800A6F28, object, 1);
    func_8005A648(object);
    func_8005A648(&D_800A6F28);
    return 0;
}
