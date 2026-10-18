typedef struct Page {
    char pad0[0xA1];
    unsigned char flag0;
    char pad1[0xC1 - 0xA2];
    unsigned char flag1;
    char pad2[0xC8 - 0xC2];
    int *style0;
    char pad3[0xE1 - 0xCC];
    unsigned char flag2;
    char pad4[0x101 - 0xE2];
    unsigned char flag3;
    char pad5[0x108 - 0x102];
    int *style1;
} Page;

typedef struct Menu {
    int pad;
    Page *page;
    int pad2[3];
    unsigned short index;
} Menu;

typedef struct Controller {
    char pad[6];
    unsigned short flags;
    char pad2[0x84];
} Controller;

extern int D_800EAD64;
extern int D_800EADD0;
extern Controller D_800EE028[];
extern int D_800C60D0;
extern int D_800C60DC;
extern unsigned char D_800ABA5A;
extern short D_800ABA54[];
extern short D_800ABA58;
extern int D_800ABA38;
extern int func_800862D4(int);
extern int func_8008623C(int);
extern void func_8005A2F0(void *, void *);
extern void func_80054CA0(void);
extern void func_8006AFC0(int);
extern void func_8005AC50(void *);

int func_80061618(Menu *menu) {
    if (func_800862D4(0)) {
        menu->page->style0 = &D_800EAD64;
    } else {
        menu->page->style0 = &D_800EADD0;
    }
    if (func_800862D4(1)) {
        menu->page->style1 = &D_800EAD64;
    } else {
        menu->page->style1 = &D_800EADD0;
    }
    if (func_8008623C(0)) {
        menu->page->flag0 &= 0xFE;
        menu->page->flag1 &= 0xFE;
        menu->page->flag0 |= 0x10;
        menu->page->flag1 = 3;
    } else {
        if (menu->page->flag0 & 0x80) {
            func_8005A2F0((char *)menu->page + 0xA0, (char *)menu->page + 0x20);
        }
        menu->page->flag0 = 1;
        menu->page->flag1 = 1;
    }
    if (func_8008623C(1)) {
        menu->page->flag2 &= 0xFE;
        menu->page->flag3 &= 0xFE;
        menu->page->flag2 |= 0x10;
        menu->page->flag3 = 3;
    } else {
        if (menu->page->flag2 & 0x80) {
            func_8005A2F0((char *)menu->page + 0xE0, (char *)menu->page + 0x20);
        }
        menu->page->flag2 = 1;
        menu->page->flag3 = 1;
    }
    if ((D_800EE028[menu->index].flags & 8) && D_800C60D0 == 7) {
        D_800C60DC = 5;
        D_800ABA5A = 0;
        func_80054CA0();
        func_8006AFC0(1);
        D_800ABA54[0] = 0;
        D_800ABA54[1] = 0;
        D_800ABA58 = 0;
        func_8005AC50(&D_800ABA38);
        return 3;
    }
    return 0;
}
