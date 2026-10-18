typedef struct {
    unsigned char used;
    unsigned char flags;
    char pad2[30];
} Item;
typedef struct {
    char pad0[4];
    Item *items;
} ItemList;

static inline Item *find_selected(ItemList *list) {
    Item *item;

    for (item = list->items; item->used != 0; item++) {
        if (item->flags & 0x80) {
            return item;
        }
    }
    return 0;
}

static inline Item *find_previous_selectable(Item *first, Item *from) {
    Item *item;

    for (item = from - 1; item >= first; item--) {
        if (item->flags & 0x10) {
            return item;
        }
    }
    return 0;
}

void func_8005A648(ItemList *list) {
    Item *cur;
    Item *prev;

    for (;;) {
        cur = find_selected(list);
        if (cur == 0) {
            return;
        }
        prev = find_previous_selectable(list->items, cur);
        if (prev == 0) {
            return;
        }
        cur->flags &= 0x7F;
        prev->flags |= 0x80;
    }
}
