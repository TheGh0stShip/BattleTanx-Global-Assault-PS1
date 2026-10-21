typedef struct Menu Menu;
typedef struct Item Item;
struct Item {
    unsigned char valid;
    unsigned char flags;
    char pad2[0xE];
    void *widget;
    int (*on_select)(Menu *, Item *);
    int (*on_left)(Menu *, Item *);
    int (*on_right)(Menu *, Item *);
};
typedef struct {
    short (*update)(Menu *);
    void (*up)(Menu *);
    void (*down)(Menu *);
    void (*extra)(Menu *);
    short (*back)(Menu *);
} Handlers;
typedef struct {
    int up;
    int down;
    int back;
    int extra;
    int select;
    int left;
    int right;
} Keys;
struct Menu {
    char pad0[4];
    Item *items;
    char pad8[4];
    Keys *keys;
    Handlers *handlers;
    unsigned short player;
};
typedef struct {
    char pad0[6];
    unsigned short pressed;
    char pad8[0x8C - 8];
} Pad;
extern Pad D_800EE028[];
extern unsigned char func_800762CC(void);
extern int func_80054A30(unsigned char);
extern short func_80058E18(Menu *, Item *);

static inline Item *find_selected(Item *p) {
    for (; p->valid != 0; p++) {
        if (p->flags & 0x80) {
            return p;
        }
    }
    return 0;
}

short func_800591C8(Menu *menu) {
    Handlers *h = menu->handlers;
    Keys *keys;
    Item *item;
    int ret;
    short r;

    if (h->update != 0 && (r = h->update(menu)) != 0) {
        return r;
    }
    keys = menu->keys;
    if (func_800762CC() != 0) {
        int pressed = D_800EE028[menu->player].pressed;

        if (h->up != 0 && (pressed & keys->up)) {
            h->up(menu);
            func_80054A30(3);
        } else if (h->down != 0 && (pressed & keys->down)) {
            h->down(menu);
            func_80054A30(3);
        }
        if (pressed & keys->select) {
            item = find_selected(menu->items);
            if (item != 0 && item->on_select != 0) {
                func_80054A30(3);
                ret = item->on_select(menu, item);
                goto done;
            }
        }
        if (pressed & keys->left) {
            item = find_selected(menu->items);
            if (item != 0 && item->on_left != 0) {
                func_80054A30(3);
                return item->on_left(menu, item);
            }
        }
        if (pressed & keys->right) {
            item = find_selected(menu->items);
            if (item != 0 && item->on_right != 0) {
                func_80054A30(3);
                return item->on_right(menu, item);
            }
        }
        if (h->extra != 0 && (pressed & keys->extra)) {
            h->extra(menu);
        }
        if (pressed & keys->back) {
            func_80054A30(3);
            if (h->back != 0) {
                r = h->back(menu);
                if (r == 1 || r == 3) {
                    return r;
                }
            } else {
                return 1;
            }
        }
    }
    for (item = menu->items; item->valid != 0; item++) {
        if (item->widget != 0) {
            ret = func_80058E18(menu, item);
            if (ret == 1) {
                goto done;
            }
            if (ret == 3) {
                goto done;
            }
        }
    }
    ret = 0;
done:
    return ret;
}
