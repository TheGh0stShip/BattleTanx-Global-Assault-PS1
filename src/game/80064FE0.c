typedef struct Dialog {
    char pad0[0x28];
    int *style;
    char pad1[0x280 - 0x2C];
    unsigned char active;
    char pad2[0x2A8 - 0x281];
    int *button_style;
} Dialog;

extern Dialog D_800ABD60;
extern int D_800EADA4;
extern int D_800EAE20;
extern int D_800E53FC;
extern unsigned char D_800E534C;
extern void func_8006A5F4(int *, unsigned char *);
extern void func_80064510(int, int, int, unsigned short, short, int, int, short);

void func_80064FE0(int a, int b, int c, unsigned short d, short e, int f, int g, short h) {
    int scratch[2];

    D_800ABD60.style = &D_800EADA4;
    if (D_800E53FC != 55) {
        func_8006A5F4(scratch, &D_800E534C);
        D_800ABD60.active = 6;
    } else {
        D_800E534C = 0;
        D_800ABD60.active = 1;
    }
    D_800ABD60.button_style = &D_800EAE20;
    func_80064510(a, b, c, d, e, f, g, h);
}
