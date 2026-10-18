typedef struct Choice {
    int key;
    int name;
    int icon;
} Choice;

extern char D_800AA2A8[];
extern char D_800AA348[];
extern char D_800AA3E8[];
extern char D_800AA488[];
extern char D_800AAA18[];
extern char D_800AAAB8[];
extern char D_800AAB58[];
extern char D_800AABF8[];
extern signed char D_800A60DC[];
extern unsigned char D_800AED4D;
extern unsigned char D_800AED4E;
extern unsigned char D_800A5B78;
extern int D_800A60C4[];
extern Choice D_800A9AFC[];
extern void func_8005CE04(void *, unsigned short);

int func_8005D130(char *menu) {
    unsigned short player;
    signed char *choice;
    signed char old;

    if (menu == D_800AA2A8 || menu == D_800AAA18) {
        player = 0;
    } else if (menu == D_800AA348 || menu == D_800AAAB8) {
        player = 1;
    } else if (menu == D_800AA3E8 || menu == D_800AAB58) {
        player = 2;
    } else if (menu == D_800AA488 || menu == D_800AABF8) {
        player = 3;
    } else {
        return 0;
    }
    choice = &D_800A60DC[player];
    old = *choice;
    *choice = old - 1;
    if (*choice == 2) {
        if (!(D_800AED4D & 1)) {
            *choice = old - 2;
        }
    } else if (*choice == 3) {
        if (!(D_800AED4E & 1)) {
            if (D_800AED4D & 1) {
                *choice = old - 2;
            } else {
                *choice = old - 3;
            }
        }
    }
    if (D_800A60DC[player] < 0) {
        D_800A60DC[player] = D_800A5B78 + 11;
    }
    func_8005CE04(menu, player);
    D_800A60C4[player] = D_800A9AFC[D_800A60DC[player]].key;
    return 0;
}
