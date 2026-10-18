typedef struct Dialog {
    char pad0[0x28];
    int *style;
    char pad1[0x280 - 0x2C];
    unsigned char active;
    char pad2[0x2A8 - 0x281];
    int *button_style;
} Dialog;

extern Dialog D_800ABD60;
extern int D_800EAE0C;
extern int D_800EAE20;
extern unsigned char D_800E534C;
extern void func_80064510(int, int, int, unsigned short, short, int, int, int);

void func_800650DC(int a, int b, int c, unsigned short d, short e, int f, int g) {
    D_800ABD60.style = &D_800EAE0C;
    D_800ABD60.button_style = &D_800EAE20;
    D_800E534C = 0;
    D_800ABD60.active = 1;
    func_80064510(a, b, c, d, e, f, g, 0);
}
