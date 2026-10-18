typedef struct Choice {
    int key;
    int name;
    int icon;
} Choice;

typedef struct Page {
    char pad[0x48];
    int icon;
} Page;

typedef struct Menu {
    int pad;
    Page *page;
} Menu;

extern Menu D_800AA2A8;
extern Menu D_800AA348;
extern Menu D_800AA3E8;
extern Menu D_800AA488;
extern Menu D_800AAA18;
extern Menu D_800AAAB8;
extern Menu D_800AAB58;
extern Menu D_800AABF8;
extern signed char D_800A606C;
extern signed char D_800A60DC[];
extern int D_800A60C4[];
extern Choice D_800A9AFC[];
extern unsigned char D_800AACD4;
extern void func_8005CE04(Menu *, unsigned short);

static inline void set_choice_icon(Menu *menu, unsigned short player) {
    menu->page->icon = D_800A9AFC[D_800A60DC[player]].icon;
}

int func_8005D2D4(void) {
    signed char i;
    Menu *menu;

    for (i = 0; i < 4; i++) {
        if (D_800A606C == 1) {
            switch (i) {
            case 0:
                menu = &D_800AA2A8;
                break;
            case 1:
                menu = &D_800AA348;
                break;
            case 2:
                menu = &D_800AA3E8;
                break;
            default:
                menu = &D_800AA488;
                break;
            }
        } else {
            switch (i) {
            case 0:
                menu = &D_800AAA18;
                break;
            case 1:
                menu = &D_800AAAB8;
                break;
            case 2:
                menu = &D_800AAB58;
                break;
            default:
                menu = &D_800AABF8;
                break;
            }
        }
        set_choice_icon(menu, i);
        D_800A60C4[i] = D_800A9AFC[D_800A60DC[i]].key;
    }
    if (D_800A606C == 1) {
        D_800AACD4 = 100;
        func_8005CE04(menu, 0);
    } else {
        D_800AACD4 = 100;
        func_8005CE04(menu, 0);
        func_8005CE04(menu, 1);
    }
    return 1;
}
