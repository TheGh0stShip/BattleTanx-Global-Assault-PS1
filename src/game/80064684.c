typedef struct Dialog {
    char data[0x400];
} Dialog;

extern short D_800E52CC;
extern int D_800ABA84;
extern int D_800E5308;
extern int D_800E5330;
extern int D_800E52B8;
extern int D_800E530C;
extern int D_800E5334;
extern short D_800E533C;
extern short D_800E5340;
extern int *D_800AC148;
extern int *D_800AC228;
extern int D_800EAE14;
extern int D_800EAF58;
extern short D_800E52D4;
extern short D_800E52D8;
extern short D_800E52F4;
extern int D_800E52B4;
extern int D_800E5338;
extern int D_800E52D0;
extern int D_800E52C0;
extern int D_800E52DC;
extern Dialog D_800AC080;
extern int D_800AC464;
extern void func_8005A888(void);
extern void func_800642C0(int, int *);
extern void func_80059550(void *, void *, int);

void func_80064684(int start, int end, int c, int d, unsigned short e, unsigned short f, short step0,
                   short step1, int text0, int text1, short h) {
    D_800E52CC = 0;
    D_800ABA84 = 0;
    func_8005A888();
    D_800E5308 = 0;
    D_800E5330 = c;
    D_800E52B8 = 0;
    D_800E530C = 0;
    D_800E5334 = d;
    D_800E533C = e;
    D_800E5340 = f;
    if (step0 <= 0) {
        D_800AC148 = &D_800EAF58;
        D_800E52D4 = -step0;
    } else {
        D_800AC148 = &D_800EAE14;
        D_800E52D4 = step0;
    }
    if (step1 <= 0) {
        D_800AC228 = &D_800EAF58;
        D_800E52D8 = -step1;
    } else {
        D_800AC228 = &D_800EAE14;
        D_800E52D8 = step1;
    }
    D_800E52B4 = text1;
    D_800E5338 = start;
    D_800E52D0 = end;
    D_800E52F4 = h;
    func_800642C0(text0, &D_800E52C0);
    func_800642C0(D_800E52B4, &D_800E52DC);
    D_800AC080.data[0x80] = 1;
    D_800AC080.data[0xA0] = 1;
    D_800AC080.data[0xC0] = 1;
    D_800AC080.data[0xE0] = 1;
    D_800AC080.data[0x100] = 1;
    D_800AC080.data[0x120] = 1;
    D_800AC080.data[0x160] = 1;
    D_800AC080.data[0x180] = 1;
    D_800AC080.data[0x1A0] = 1;
    D_800AC080.data[0x1C0] = 1;
    D_800AC080.data[0x1E0] = 1;
    D_800AC080.data[0x200] = 1;
    D_800AC080.data[0x220] = 1;
    D_800AC080.data[0x240] = 1;
    D_800AC080.data[0x260] = 1;
    D_800AC080.data[0x280] = 1;
    D_800AC080.data[0x2A0] = 1;
    D_800AC080.data[0x2C0] = 1;
    D_800AC080.data[0x2E0] = 1;
    D_800AC080.data[0x300] = 1;
    D_800AC080.data[0x320] = 1;
    D_800AC080.data[0x380] = 1;
    func_80059550(&D_800AC464, 0, 1);
}
