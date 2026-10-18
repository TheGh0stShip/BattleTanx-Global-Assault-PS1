typedef struct Widget Widget;
typedef struct {
    unsigned char valid;
    char pad1[0xF];
    Widget *widget;
    char pad14[0x20 - 0x14];
} Item;
typedef struct {
    char pad0[4];
    Item *items;
} Menu;
typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];
extern short func_800591C8(void *);
extern void func_8005992C(unsigned short);
extern short func_80058E18(Menu *, Item *);

void func_80059BB8(void) {
    short i;
    Channel *c;

    for (i = 0; i < 10; i++) {
        c = &D_800E474C[i];

        if (c->flags & 2) {
            short r = func_800591C8(c->stream);

            if (r == 1 && c->state >= 0) {
                func_8005992C(i);
            } else if (r == 3) {
                short k = i;

                while (D_800E474C[k].state >= 0) {
                    k = D_800E474C[k].state;
                }
                func_8005992C(k);
            }
        } else if (c->flags & 1) {
            Menu *menu = c->stream;
            Item *item;

            for (item = menu->items; item->valid != 0; item++) {
                if (item->widget != 0) {
                    short r = func_80058E18(menu, item);

                    if (r == 1) {
                        break;
                    }
                    if (r == 3) {
                        break;
                    }
                }
            }
        }
    }
    for (i = 0; i < 10; i++) {
        c = &D_800E474C[i];
        if (c->flags & 0x40) {
            c->flags = (c->flags & ~0x40) | 2;
        }
    }
}
