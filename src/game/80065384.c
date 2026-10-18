typedef struct Menu {
    int pad;
    unsigned char *base;
} Menu;

extern signed char D_800A606C;
extern int func_800851D4(void);
extern void func_8005A2F0(void *, void *);

int func_80065384(Menu *menu) {
    if (func_800851D4() & 2) {
        menu->base[0xA1] &= 0xFE;
        menu->base[0xA1] |= 0x10;
    } else {
        if (menu->base[0xA1] & 0x80) {
            func_8005A2F0(menu->base + 0xA0, menu->base + 0x80);
        }
        if (D_800A606C == 2) {
            D_800A606C = 1;
        }
        menu->base[0xA1] = 1;
    }
    return 0;
}
