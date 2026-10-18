typedef struct Menu {
    int pad;
    char *base;
} Menu;

extern int D_800C60C8;
extern int D_800C60DC;
extern int D_800A6070;
extern unsigned char D_800AEA46;
extern unsigned char D_800ABA5B;
extern unsigned char D_800AAD00;
extern int D_800A66FC;
extern void func_80054D4C(void);
extern void func_8006AFFC(int);
extern void func_8006A290(void);
extern void func_8005A2F0(int, void *);
extern void func_800611D4(void *);

int func_80063FFC(Menu *menu, int arg) {
    D_800C60C8 = 0;
    D_800C60DC = 2;
    func_80054D4C();
    func_8006AFFC(0);
    D_800AEA46 = 100;
    if (D_800A6070 == 1) {
        D_800ABA5B = 0;
        func_8006A290();
    } else {
        D_800ABA5B = 0;
    }
    D_800AAD00 = 2;
    func_8005A2F0(arg, menu->base + 0x60);
    func_800611D4(&D_800A66FC);
    return 3;
}
