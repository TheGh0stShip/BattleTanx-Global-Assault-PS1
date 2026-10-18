typedef struct Item {
    char pad[0x14];
    unsigned short index;
} Item;

typedef struct Element {
    char pad[0x28];
    int *style;
} Element;

extern unsigned int D_800EC0F8[];
extern int D_800EAE68;
extern int D_800EAC6C;
extern int D_800EAC60;
extern int D_800EAC48;
extern int D_800EAC4C;
extern int D_800EADCC;
extern int D_800EAD00;

static inline void select_item_style(Item *item, Element *element) {
    switch (D_800EC0F8[item->index]) {
    case 0:
        element->style = &D_800EAE68;
        break;
    case 1:
        element->style = &D_800EAC6C;
        break;
    case 2:
        element->style = &D_800EAC60;
        break;
    case 3:
        element->style = &D_800EAC48;
        break;
    case 4:
        element->style = &D_800EAC4C;
        break;
    case 5:
        element->style = &D_800EADCC;
        break;
    case 6:
        element->style = &D_800EAD00;
        break;
    case 7:
        break;
    }
}

int func_8005BD58(Item *item, Element *element) {
    if (D_800EC0F8[item->index] == 0) {
        D_800EC0F8[item->index] = 6;
    } else {
        D_800EC0F8[item->index]--;
    }
    if (D_800EC0F8[item->index] == 2) {
        D_800EC0F8[item->index] = 1;
    }
    select_item_style(item, element);
    return 0;
}
