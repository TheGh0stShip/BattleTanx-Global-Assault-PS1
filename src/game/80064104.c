typedef struct Menu {
    int pad;
    char *base;
} Menu;

typedef struct Element {
    int pad[10];
    int *style;
} Element;

typedef struct Group {
    int pad;
    Element *element;
    int pad2[3];
    short value;
} Group;

extern Menu D_800AB604;
extern Group D_800AB7B0;
extern unsigned char D_800ABA5A;
extern int D_800EAC94;
extern int D_800EAE4C;
extern void func_8005A2F0(int, void *);
extern void func_80059550(void *, void *, int);

int func_80064104(Menu *menu, int arg) {
    if (menu == &D_800AB604) {
        D_800AB7B0.element->style = &D_800EAE4C;
    } else {
        D_800AB7B0.element->style = &D_800EAC94;
    }
    func_8005A2F0(arg, menu->base + 0x20);
    D_800AB7B0.value = D_800ABA5A;
    func_80059550(&D_800AB7B0, menu, 1);
    return 0;
}
