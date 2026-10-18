typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];
extern void func_80059004(void *);

void func_80059550(void *menu, void *parent_stream, unsigned short mode) {
    short i;
    short slot;
    Channel *c;
    Channel *p;
    unsigned short flags;

    if (mode == 2) {
        if (parent_stream == 0) {
            return;
        }
        for (i = 0; i < 10; i++) {
            if (D_800E474C[i].flags != 0 && D_800E474C[i].stream == parent_stream) {
                break;
            }
        }
        if (i == 10) {
            return;
        }
        D_800E474C[i].flags = 0xC1;
        D_800E474C[i].stream = menu;
        func_80059004(menu);
        return;
    }
    for (i = 0; i < 10; i++) {
        if (D_800E474C[i].flags == 0) {
            break;
        }
    }
    c = &D_800E474C[i];
    slot = i;
    if (mode == 3) {
        c->flags = 0x81;
    } else {
        c->flags = 0xC1;
    }
    c->sounds[0] = -1;
    c->sounds[1] = -1;
    c->sounds[2] = -1;
    c->sounds[3] = -1;
    c->sounds[4] = -1;
    c->sounds[5] = -1;
    c->stream = menu;
    func_80059004(menu);
    if (parent_stream != 0) {
        for (i = 0; i < 10; i++) {
            if (D_800E474C[i].flags != 0 && D_800E474C[i].stream == parent_stream) {
                break;
            }
        }
        if (i == 10) {
            c->state = -1;
            p = 0;
        } else {
            c->state = i;
            p = &D_800E474C[i];
        }
    } else {
        c->state = -1;
        p = 0;
    }
    if (p != 0) {
        for (i = 0; i < 6; i++) {
            if (p->sounds[i] == -1) {
                p->sounds[i] = slot;
                break;
            }
        }
        flags = p->flags;
        p->flags = flags & ~2;
        if (mode == 1) {
            p->flags = flags & ~3;
        }
    }
}
