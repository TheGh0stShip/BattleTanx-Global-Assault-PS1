typedef struct Choice {
    int key;
    int name;
    int icon;
} Choice;

typedef struct Menu {
    int pad;
    unsigned char *base;
} Menu;

extern Menu D_800AA2A8;
extern Menu D_800AA348;
extern Menu D_800AA3E8;
extern Menu D_800AA488;
extern Menu D_800AA4E8;
extern Menu D_800AAA18;
extern Menu D_800AAAB8;
extern Menu D_800AAB58;
extern Menu D_800AABF8;
extern Menu D_800AAC58;
extern Menu D_800AACB8;
extern signed char D_800A606C;
extern int D_800A6084[];
extern signed char D_800A60DC[];
extern int D_800A60C4[];
extern Choice D_800A9AFC[];
extern void func_8005A7E0(Menu *);
extern void func_8005A834(Menu *);
extern void func_8005CE04(Menu *, unsigned short);

void func_8005D9FC(Menu *menu) {
    Menu *next;
    int player;
    unsigned short slot;
    unsigned char *base;

    player = 0;
    next = menu;
    if (D_800A606C == 1) {
        if (menu == &D_800AA2A8) {
            next = &D_800AA348;
        } else if (menu == &D_800AA348) {
            player = 1;
            next = &D_800AA3E8;
        } else if (menu == &D_800AA3E8) {
            player = 2;
            next = &D_800AA488;
        } else if (menu == &D_800AA488) {
            player = 3;
            next = &D_800AA4E8;
        } else {
            next = &D_800AA2A8;
        }
    } else {
        if (menu == &D_800AAA18) {
            next = &D_800AAB58;
        } else if (menu == &D_800AAB58) {
            player = 2;
            next = &D_800AAC58;
        } else if (menu == &D_800AAC58) {
            next = &D_800AAA18;
        } else if (menu == &D_800AAAB8) {
            player = 1;
            next = &D_800AABF8;
        } else if (menu == &D_800AABF8) {
            player = 3;
            next = &D_800AACB8;
        } else if (menu == &D_800AACB8) {
            next = &D_800AAAB8;
        }
    }
    if (menu != &D_800AA4E8 && menu != &D_800AAC58 && menu != &D_800AACB8) {
        base = menu->base;
        base[0x21] = 16;
        if (D_800A6084[player] == 0) {
            base[0x40] = 1;
            base[0x60] = 1;
            base[0x41] = 1;
            base[0x61] = 1;
        } else {
            base[0x40] = 4;
            base[0x60] = 4;
            base[0x41] = 16;
            base[0x61] = 16;
        }
    } else {
        menu->base[0x21] = 16;
    }
    func_8005A7E0(menu);
    if (menu == &D_800AA488 || menu == &D_800AABF8 || menu == &D_800AAB58) {
        next->base[0x21] = 0x90;
        func_8005A834(next);
        return;
    }
    base = next->base;
    base[0x21] = 0x90;
    func_8005A834(next);
    if (next == &D_800AA2A8 || next == &D_800AAA18) {
        slot = 0;
    } else if (next == &D_800AA348 || next == &D_800AAAB8) {
        slot = 1;
    } else if (next == &D_800AA3E8 || next == &D_800AAB58) {
        slot = 2;
    } else if (next == &D_800AA488 || next == &D_800AABF8) {
        slot = 3;
    } else {
        return;
    }
    func_8005CE04(next, slot);
    D_800A60C4[slot] = D_800A9AFC[D_800A60DC[slot]].key;
}
