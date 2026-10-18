typedef struct {
    int min;
    int max;
} Range;
typedef struct {
    unsigned short type;
    short pad2;
    int value;
    void *data;
} Widget;
typedef struct {
    unsigned short base;
    unsigned short current;
    short delta;
} Cursor;
typedef struct {
    char pad0[8];
    Cursor *cursor;
    char padC[4];
    Widget *widget;
} Item;
extern unsigned int func_80086C84(void);
extern void func_80058E18(void *, Item *);

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

void func_8005A964(void *menu, Item *item) {
    Widget *w;
    Range *r;

    if (item->widget == 0) {
        return;
    }
    w = item->widget;
    switch (w->type) {
    case 1:
        r = w->data;
        w->value = ((func_80086C84() % (to_int(r->max) - to_int(r->min))) + to_int(r->min)) << 12;
        break;
    case 0:
    case 2:
    case 3:
    case 4:
        w->value = ((int *)w->data)[0];
        break;
    case 5:
        w->value = ((int *)w->data)[1];
        break;
    case 6:
        w->value = *(unsigned short *)w->data;
        item->cursor->current = item->cursor->base;
        item->cursor->delta = 0;
        break;
    case 7:
    case 8:
    case 9:
        break;
    }
    func_80058E18(menu, item);
}
