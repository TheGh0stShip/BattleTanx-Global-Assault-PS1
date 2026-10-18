typedef struct {
    char pad0[8];
    char *label;
    char padC[0x20 - 0xC];
} Item;
extern int D_800A6070;
extern char D_800EAE88[];
extern char D_800EAF40[];
extern char D_800EADC0[];
extern char D_800EAEFC[];
extern char D_800EAF04[];
extern char D_800EAEF4[];
extern char D_800EAEE8[];
extern char D_800EAC3C[];

int func_8005AE98(int unused, Item *items) {
    if (++D_800A6070 == 2) {
        D_800A6070++;
    }
    if (D_800A6070 > 8U) {
        D_800A6070 = 1;
    }
    items++;
    switch (D_800A6070) {
    case 5:
        items->label = D_800EAE88;
        break;
    case 6:
        items->label = D_800EAF40;
        break;
    case 4:
        items->label = D_800EADC0;
        break;
    case 3:
        items->label = D_800EAEFC;
        break;
    case 7:
        items->label = D_800EAF04;
        break;
    case 8:
        items->label = D_800EAEF4;
        break;
    case 2:
        items->label = D_800EAEE8;
        break;
    case 1:
    default:
        items->label = D_800EAC3C;
        break;
    }
    return 0;
}
