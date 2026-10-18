typedef struct Menu {
    int pad;
    char *base;
} Menu;

extern int D_800C60E4;
extern int D_800C60C8;
extern int D_800A6070;
extern char D_800A4381;
extern int D_800A48DC;
extern short D_800ABA54[];
extern short D_800ABA58;
extern void func_800203E0(void);
extern void func_80054D4C(void);
extern void func_8005A2F0(int, void *);

int func_80063F44(Menu *menu, int arg) {
    D_800C60E4 = -1;
    if (D_800A6070 == 1) {
        D_800C60C8 = 0;
        D_800A4381 = 1;
        D_800A48DC = 1;
        func_800203E0();
        D_800A4381 = 0;
    } else {
        D_800C60C8 = 0;
        D_800A48DC = 1;
    }
    D_800ABA54[0] = 0;
    D_800ABA54[1] = 0;
    D_800ABA58 = 0;
    func_80054D4C();
    if (menu != 0) {
        func_8005A2F0(arg, menu->base + 0x60);
    }
    return 3;
}
