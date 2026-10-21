typedef struct Widget Widget;
typedef struct Item Item;
typedef struct {
    int speed;
    char pad4[4];
    unsigned short step;
    short limit;
} Slide;
typedef struct {
    unsigned short wait;
} Blink;
typedef struct {
    char pad0[4];
    short phase;
} Cursor;
struct Widget {
    unsigned short type;
    short pad2;
    int value;
    void *data;
    Widget *next;
};
struct Item {
    char pad0[2];
    unsigned short pos;
    short offset;
    char pad6[2];
    Cursor *cursor;
    char padC[4];
    Widget *widget;
};
extern short func_80058B9C(Item *);
extern unsigned short func_800569EC(Cursor *);
extern void func_8005A964(void *, Item *);

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

int func_80058E18(void *menu, Item *item) {
    short done = 0;

    switch (item->widget->type) {
    case 0:
    case 1: {
        Widget *w = item->widget;

        if (w->value == 0) {
        idle:
            __asm__("");
            done = 0;
            break;
        }
        w->value -= 4096;
        if (w->value <= 0) {
            goto finished;
        }
        done = 0;
        break;
    }
    case 2:
    case 3:
    case 4:
        done = func_80058B9C(item);
        break;
    case 5: {
        Widget *w = item->widget;
        Slide *s = w->data;

        item->offset += to_int(w->value);
        item->pos += s->step;
        if (item->offset >= s->limit) {
            item->offset = s->limit;
        finished:
            done = 1;
        } else {
            w->value += s->speed;
            done = 0;
        }
        break;
    }
    case 6: {
        Cursor *cur = item->cursor;
        Widget *w = item->widget;
        Blink *b = w->data;

        if (func_800569EC(cur) == 0) {
            goto idle;
        }
        if (b->wait != 0) {
            w->value -= 4096;
            if (w->value <= 0) {
                goto finished;
            }
        }
        cur->phase = 0;
        goto idle;
    }
    case 7:
        done = ((short (*)(void *, Item *))item->widget->data)(menu, item);
        break;
    case 8:
        return 1;
    case 9:
        return 3;
    }
    if (done) {
        item->widget = item->widget->next;
        func_8005A964(menu, item);
    }
    return 0;
}
