typedef struct {
    unsigned char valid;
    unsigned char flags;
    char pad2[6];
    char *data;
    char padC[0x20 - 0xC];
} Item;
typedef struct {
    char pad0[4];
    Item *items;
    char pad8[0x14 - 8];
    unsigned short player;
} Menu;
typedef struct {
    int type;
    char pad4[0x8C - 4];
} Pad;
extern Pad D_800EE028[];
extern unsigned char D_800AACE5;
extern unsigned char D_800AACE4;
extern int D_800EC0F8[];
extern unsigned char D_800A947C[];
extern char D_800EAC54[];
extern char D_800EAC58[];
extern char D_800EAC5C[];
extern char D_800EAC64[];
extern char D_800EAC68[];
extern char D_800EAD38[];
extern char D_800EAD3C[];
extern char D_800EAD68[];
extern char D_800EAD84[];
extern char D_800EAD8C[];
extern char D_800EAD9C[];
extern char D_800EADC8[];
extern char D_800EADDC[];
extern char D_800EAE18[];
extern char D_800EAEF8[];
extern char D_800EAF00[];
extern char D_800EADD0[];
extern char D_800EAE94[];
extern char D_800EAE90[];
extern char D_800EAD64[];
extern int func_800862D4(int);
extern int func_8008623C(int);
extern void func_8005A2F0(Item *, Item *);

int func_8005B6A8(Menu *menu) {
    unsigned char i;

    if (D_800AACE5 != 1 && D_800AACE4 != 0) {
        menu->items[2].data = D_800EAE94;
        menu->player = 1;
    } else {
        menu->items[2].data = D_800EAE90;
        menu->player = 0;
    }
    if (func_800862D4(menu->player) != 0) {
        menu->items[6].data = D_800EAD64;
    } else {
        menu->items[6].data = D_800EADD0;
    }
    if (func_8008623C(menu->player) != 0) {
        menu->items[5].flags &= ~1;
        menu->items[6].flags &= ~1;
        menu->items[5].flags |= 0x10;
        menu->items[6].flags = 3;
    } else {
        if (menu->items[5].flags & 0x80) {
            func_8005A2F0(&menu->items[5], &menu->items[3]);
        }
        menu->items[5].flags = 1;
        menu->items[6].flags = 1;
    }
    for (i = 9; i < 20; i++) {
        int type = D_800EE028[(unsigned char)menu->player].type;

        if ((type == 1 || type == 5) && (unsigned char)(i - 12) < 2) {
            menu->items[i].data = D_800EADD0;
            continue;
        }
        switch (D_800A947C[i - 9 + D_800EC0F8[menu->player] * 11]) {
        case 0:
            menu->items[i].data = D_800EADD0;
            break;
        case 1:
            menu->items[i].data = D_800EAC58;
            break;
        case 2:
            menu->items[i].data = D_800EAC54;
            break;
        case 3:
            menu->items[i].data = D_800EAC5C;
            break;
        case 4:
            menu->items[i].data = D_800EADC8;
            break;
        case 5:
            menu->items[i].data = D_800EAC64;
            break;
        case 6:
            menu->items[i].data = D_800EAC68;
            break;
        case 7:
            menu->items[i].data = D_800EAD84;
            break;
        case 8:
            menu->items[i].data = D_800EAD8C;
            break;
        case 9:
            menu->items[i].data = D_800EAD3C;
            break;
        case 10:
            menu->items[i].data = D_800EAF00;
            break;
        case 11:
            menu->items[i].data = D_800EAD68;
            break;
        case 12:
            menu->items[i].data = D_800EAE18;
            break;
        case 13:
            menu->items[i].data = D_800EADDC;
            break;
        case 14:
            menu->items[i].data = D_800EAD9C;
            break;
        case 15:
            menu->items[i].data = D_800EAEF8;
            break;
        case 16:
            menu->items[i].data = D_800EAD38;
            break;
        }
    }
    return 0;
}
