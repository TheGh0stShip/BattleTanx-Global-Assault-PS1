typedef struct Choice {
    unsigned char id;
    int name;
    int icon;
} Choice;

typedef struct Screen {
    char pad0[0x288];
    int name0;
    char pad1[0x2A8 - 0x28C];
    int name1;
    char pad2[0x2C8 - 0x2AC];
    int name_single;
} Screen;

typedef struct Page {
    char pad[0x48];
    volatile int icon;
} Page;

typedef struct Menu {
    int pad;
    Page *page;
} Menu;

extern signed char D_800A60DC[];
extern signed char D_800A606C;
extern Choice D_800A9AFC[];
extern int D_800A6084[];
extern Screen *volatile D_800AA20C;
extern Screen *volatile D_800AA97C;
extern void func_8005FB70(int);
extern void func_8005FBD4(int);

void func_8005CE04(Menu *menu, unsigned short player) {
    unsigned char index;
    Page *page;
    Choice *choice;
    Screen *screen;

    index = D_800A60DC[player];
    page = menu->page;
    if (D_800A606C == 1) {
        {
            Choice *tab = D_800A9AFC;
            choice = tab + index;
        }
        page->icon = choice->icon;
        screen = D_800AA20C;
        if (D_800A6084[player] != 0) {
            screen->name_single = choice->name;
            func_8005FB70(choice->id);
        }
    } else {
        Choice *tab = D_800A9AFC;

        choice = &tab[(unsigned char)index];
        page->icon = choice->icon;
        screen = D_800AA97C;
        if (player == 0 || player == 2) {
            if (D_800A6084[player] != 0) {
                screen->name0 = choice->name;
                func_8005FB70(tab[D_800A60DC[player]].id);
            }
        } else if (D_800A6084[player] != 0) {
            screen->name1 = choice->name;
            func_8005FBD4(tab[D_800A60DC[player]].id);
        }
    }
}
