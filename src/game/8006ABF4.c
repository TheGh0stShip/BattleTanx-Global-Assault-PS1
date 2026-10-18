extern int D_800C60C0;
extern int func_80090184(void);
extern unsigned char *func_80068F34(int value);
extern void func_8008DA04(void *destination, void *source);
extern void func_80092830(void *object, void *position, int value);
extern void func_8006A8E4(void *object, int value);
extern void func_80068F9C(void *object);

void func_8006ABF4(void *source) {
    if (D_800C60C0 & 1) {
        unsigned char *object = func_80068F34(func_80090184() + 0x6D);
        unsigned char *position = object + 0x6C;
        func_8008DA04(position, source);
        func_80092830(object, position, 2);
        func_8006A8E4(object, 0);
        func_80068F9C(object);
    }
}
