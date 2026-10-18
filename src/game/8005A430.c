typedef struct Item {
    unsigned char valid;
    unsigned char flags;
    char pad2[6];
    int value;
    char padC[0x20 - 0xC];
} Item;
typedef struct {
    char pad0[4];
    Item *items;
    char pad8[0x14 - 8];
    unsigned short side;
} Menu;
extern unsigned char D_800AACD7;
extern unsigned char D_800AACD8;
extern void func_8005DCD0(Menu *);
extern void func_8005D9FC(Menu *);

static inline Item *find_selected(Item *p) {
    for (; p->valid != 0; p++) {
        if (p->flags & 0x80) {
            return p;
        }
    }
    return 0;
}

static inline Item *find_selectable(Item *p) {
    for (; p->valid != 0; p++) {
        if (p->flags & 0x10) {
            return p;
        }
    }
    return 0;
}

static inline Item *find_prev_selectable(Item *first, Item *p) {
    for (; p >= first; p--) {
        if (p->flags & 0x10) {
            return p;
        }
    }
    return 0;
}

void func_8005A430(Menu *menu) {
    Item *cur;
    Item *next;

    cur = find_selected(menu->items);
    if (cur == 0) {
        return;
    }
    next = find_selectable(cur + 1);
    if (next == 0) {
        func_8005D9FC(menu);
    } else {
        cur->flags &= 0x7F;
        next->flags |= 0x80;
    }
    if (menu->side == 0) {
        if (D_800AACD7 != 0) {
            D_800AACD7 = 0;
        }
    } else if (D_800AACD8 != 0) {
        D_800AACD8 = 0;
    }
}
