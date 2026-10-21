extern volatile int D_800B90BC[];
extern char D_800C5FB0[];
extern char D_800C5FC8[];
extern void func_800A11F4(void);
extern void func_800A1454(void);
extern void func_80097114(int);
extern void func_80097128(void *);
extern void func_80097558(void *);
extern int func_8009701C(void);
extern int func_80088870(int);
extern void func_80096F9C(char *);
extern void func_80097278(int, int);
extern int func_8009713C(int, void *, int);
extern int func_8009703C(void);
extern void func_800970B4(void);
extern int func_8009702C(void);
extern int func_800976A0(int);

int func_800A1520(int reset) {
    unsigned char status;

    func_80097114(0);
    func_80097128(0);
    if (D_800B90BC[12] & 1) {
        func_80097558(0);
    }
    if (func_8009701C() & 0x10) {
        if ((func_80088870(-1) & 0x3F) == 0) {
            func_80096F9C(D_800C5FB0);
        }
        func_80097278(1, 0);
        {
            volatile int *p = D_800B90BC;

            p[7] = func_80088870(-1);
            p[5] = -1;
            return p[5];
        }
    }
    if (reset) {
        func_80096F9C(D_800C5FC8);
        {
            register int com asm("$4") = 9;
            register void *none asm("$5") = 0;

            __asm__("" : "=r"(none) : "0"(none), "r"(com));
            func_8009713C(com, none, 0);
        }
        if (func_8009713C(2, (void *)func_8009703C(), 0) == 0) {
            volatile int *p = D_800B90BC;

            p[5] = -1;
            return D_800B90BC[5];
        }
    }
    func_800970B4();
    status = D_800B90BC[3];
    if (status != func_8009702C() || reset) {
        if (func_8009713C(14, &status, 0) == 0) {
            volatile int *p = D_800B90BC;

            p[5] = -1;
            return p[5];
        }
    }
    {
        volatile int *p = D_800B90BC;

        p[8] = func_800976A0(func_8009703C());
        func_80097128(func_800A11F4);
        if (p[12] & 1) {
            func_80097558(func_800A1454);
        }
        p[2] = p[1];
        func_80097278(6, 0);
        p[5] = p[0];
        p[6] = func_80088870(-1);
        return p[5];
    }
}
