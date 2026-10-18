typedef struct Choice {
    int key;
    int name;
    int icon;
} Choice;

typedef struct Row {
    int pad[2];
    int *target;
    char pad2[0x14];
    unsigned char state0;
    unsigned char flag0;
    char pad3[0x1E];
    unsigned char state1;
    unsigned char flag1;
} Row;

extern char D_800AA2A8[];
extern char D_800AA348[];
extern char D_800AA3E8[];
extern char D_800AA488[];
extern char D_800AAA18[];
extern char D_800AAAB8[];
extern char D_800AAB58[];
extern char D_800AABF8[];
extern unsigned int D_800A6084[];
extern signed char D_800A60DC[];
extern int D_800A60C4[];
extern Choice D_800A9AFC[];
extern int D_800EADD0;
extern int D_800EAE2C;
extern int D_800EAE40;
extern int D_800EAE44;
extern int D_800EAE48;
extern int func_8005E2EC(void);
extern void func_8005CE04(void *, unsigned short);
extern void func_8005D494(void);

static inline void refresh_player_choice(char *menu) {
    unsigned short slot;

    if (menu == D_800AA2A8 || menu == D_800AAA18) {
        slot = 0;
    } else if (menu == D_800AA348 || menu == D_800AAAB8) {
        slot = 1;
    } else if (menu == D_800AA3E8 || menu == D_800AAB58) {
        slot = 2;
    } else if (menu == D_800AA488 || menu == D_800AABF8) {
        slot = 3;
    } else {
        return;
    }
    func_8005CE04(menu, slot);
    D_800A60C4[slot] = D_800A9AFC[D_800A60DC[slot]].key;
}

int func_8005E3AC(char *menu, Row *row) {
    int player;

    if (menu == D_800AA2A8 || menu == D_800AAA18) {
        player = 0;
    } else if (menu == D_800AA348 || menu == D_800AAAB8) {
        player = 1;
    } else if (menu == D_800AA3E8 || menu == D_800AAB58) {
        player = 2;
    } else {
        player = 3;
    }
    do {
        D_800A6084[player]++;
        if (D_800A6084[player] == 5) {
            D_800A6084[player] = 0;
        }
    } while (func_8005E2EC());
    if (D_800A6084[player] == 0) {
        row->state0 = 1;
        row->state1 = 1;
        row->flag0 = 1;
        row->flag1 = 1;
    } else {
        row->state0 = 4;
        row->state1 = 4;
        row->flag0 = 16;
        row->flag1 = 16;
    }
    refresh_player_choice(menu);
    switch (D_800A6084[player]) {
    case 1:
        row->target = &D_800EAE2C;
        break;
    case 2:
        row->target = &D_800EAE48;
        break;
    case 3:
        row->target = &D_800EAE40;
        break;
    case 4:
        row->target = &D_800EAE44;
        break;
    case 0:
    default:
        row->target = &D_800EADD0;
        break;
    }
    func_8005D494();
    return 0;
}
