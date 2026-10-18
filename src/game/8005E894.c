typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

extern char D_800AA2A8[];
extern char D_800AA348[];
extern char D_800AA3E8[];
extern char D_800AAA18[];
extern char D_800AAAB8[];
extern char D_800AAB58[];
extern unsigned int D_800A6094[];
extern int D_800A60A4[];
extern int D_800EADE0;
extern int D_800EAE1C;
extern int D_800EAE24;
extern int D_800EAF64;
extern int D_800EAF68;

int func_8005E894(char *menu, Holder *holder) {
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
    D_800A6094[player]++;
    if (D_800A6094[player] >= 4) {
        D_800A6094[player] = 1;
    }
    if (D_800A60A4[player] == 1) {
        switch (D_800A6094[player]) {
        case 2:
            holder->target = &D_800EAF64;
            break;
        case 1:
            holder->target = &D_800EAE24;
            break;
        case 3:
            holder->target = &D_800EADE0;
            break;
        default:
            holder->target = &D_800EAF64;
            break;
        }
    } else {
        switch (D_800A6094[player]) {
        case 2:
            holder->target = &D_800EAF64;
            break;
        case 1:
            holder->target = &D_800EAF68;
            break;
        case 3:
            holder->target = &D_800EAE1C;
            break;
        default:
            holder->target = &D_800EAF64;
            break;
        }
    }
    return 0;
}
