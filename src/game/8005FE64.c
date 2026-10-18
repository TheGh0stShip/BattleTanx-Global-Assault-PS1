typedef struct Element {
    int pad[2];
    int *style;
} Element;

extern int D_800EAE90;
extern unsigned char D_800AACE4;
extern unsigned char D_800E482C;
extern unsigned char D_800E483C;
extern unsigned char D_800E4824;
extern int D_800EC0F8[];
extern int D_800A9838;
extern int func_800862D4(int);
extern void func_80059550(void *, void *, int);

int func_8005FE64(void *menu, Element *element) {
    signed char selection;

    if (element->style == &D_800EAE90) {
        D_800AACE4 = 0;
    } else {
        D_800AACE4 = 1;
    }
    selection = D_800AACE4;
    D_800E482C = selection;
    D_800E483C = D_800EC0F8[selection];
    if (func_800862D4(selection)) {
        D_800E4824 = 1;
    } else {
        D_800E4824 = 0;
    }
    func_80059550(&D_800A9838, menu, 1);
    return 0;
}
