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

static inline Item *find_prev_selectable(Item *first, Item *p) {
    for (; p >= first; p--) {
        if (p->flags & 0x10) {
            return p;
        }
    }
    return 0;
}

void func_80058A8C(Menu *menu) {
    Item *cur;
    Item *prev;
    Item *last;

    cur = find_selected(menu->items);
    if (cur == 0) {
        return;
    }
    prev = find_prev_selectable(menu->items, cur - 1);
    if (prev == 0) {
        for (last = cur + 1; last->valid != 0; last++) {
        }
        prev = find_prev_selectable(menu->items, last - 1);
    }
    cur->flags &= 0x7F;
    prev->flags |= 0x80;
}
