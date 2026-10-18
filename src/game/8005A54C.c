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
} Menu;

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

void func_8005A54C(Menu *menu) {
    Item *cur;
    Item *next;

    cur = find_selected(menu->items);
    if (cur == 0) {
        return;
    }
    next = find_selectable(cur + 1);
    if (next == 0) {
        next = find_selectable(menu->items);
    }
    cur->flags &= 0x7F;
    next->flags |= 0x80;
}
