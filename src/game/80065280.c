typedef struct Dialog {
    char pad0[0x28];
    int *style;
    char pad1[0x360 - 0x2C];
    unsigned char active;
    char pad2[0x388 - 0x361];
    int *button_style;
} Dialog;

extern Dialog D_800AC080;
extern int D_800EAE0C;
extern int D_800EAE20;
extern unsigned char D_800E534C;
extern void func_80064684(int, int, int, int, unsigned short, unsigned short, short, short, int, int, short);

void func_80065280(int a, int b, int c, int d, unsigned short e, unsigned short f, short g, short h, int i,
                   int j, short k) {
    D_800AC080.style = &D_800EAE0C;
    D_800AC080.button_style = &D_800EAE20;
    D_800E534C = 0;
    D_800AC080.active = 1;
    func_80064684(a, b, c, d, e, f, g, h, i, j, k);
}
