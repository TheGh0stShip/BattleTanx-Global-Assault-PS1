extern unsigned int D_800AEB30;
extern unsigned char D_800AEB38;
extern int D_800EBC3C;
extern char D_800AEB18[];
extern char D_800AEAC0[];
extern unsigned char func_800780A4(void);
extern int func_8006A388(void *);
extern void func_800203E0(void);
extern void func_80076B80(void *);
extern void func_80078940(void);
extern void func_80077A04(void);

int func_80078EC4(void) {
    switch (D_800AEB30) {
    case 0:
        break;
    case 1:
        if (func_800780A4()) {
            if (func_8006A388(D_800AEB18)) {
                func_800203E0();
            } else {
                D_800EBC3C = 9;
            }
        }
        break;
    case 2:
        if (func_800780A4()) {
            func_80076B80(D_800AEAC0);
        }
        break;
    case 3:
    case 4:
        func_80078940();
        break;
    }
    if (D_800AEB38 != 0) {
        D_800AEB38--;
    }
    func_80077A04();
    return D_800EBC3C == 14;
}
