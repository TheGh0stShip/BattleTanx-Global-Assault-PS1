typedef struct Menu {
    int pad;
    unsigned char *base;
} Menu;

extern signed char D_800A606C;
extern int func_800851D4(void);
extern void func_8005A2F0(void *, void *);

int func_80060B98(Menu *menu) {
    if (func_800851D4() & 2) {
        menu->base[0x41] &= 0xFE;
        menu->base[0x41] |= 0x10;
    } else if (D_800A606C == 1) {
        if (menu->base[0x41] & 0x80) {
            func_8005A2F0(menu->base + 0x40, menu->base + 0x80);
        }
        if (D_800A606C == 2) {
            D_800A606C = 1;
        }
        menu->base[0x41] = 1;
    }
    return 0;
}
