extern unsigned char D_800EADEC;
extern void func_8005A700(void *object, void *state);

int func_8005F3A0(void *object) {
    func_8005A700(object, &D_800EADEC);
    return 0;
}
