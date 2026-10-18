typedef struct Menu {
    int pad;
    unsigned char *base;
} Menu;

extern int func_800851D4(void);
extern void func_8005A2F0(void *, void *);

int func_8005BAAC(Menu *menu) {
    if (func_800851D4() & 1) {
        if (menu->base[0x41] & 1) {
            func_8005A2F0(0, menu->base + 0x40);
        }
        menu->base[0x41] &= 0xFE;
        menu->base[0x41] |= 0x10;
        menu->base[0x61] &= 0xFE;
        menu->base[0x61] |= 0x10;
        menu->base[0x81] &= 0xFE;
        menu->base[0x81] |= 0x10;
    } else {
        if (menu->base[0x41] & 0x80) {
            func_8005A2F0(menu->base + 0x40, 0);
        }
        menu->base[0x41] = 1;
        menu->base[0x61] = 1;
        menu->base[0x81] = 1;
    }
    if ((func_800851D4() & 2) && !(menu->base[0x41] & 1)) {
        menu->base[0x61] &= 0xFE;
        menu->base[0x61] |= 0x10;
    } else {
        if (menu->base[0x61] & 0x80) {
            func_8005A2F0(menu->base + 0x60, menu->base + 0x80);
        }
        menu->base[0x61] = 1;
    }
    return 0;
}
