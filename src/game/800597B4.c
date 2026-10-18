typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];

void func_800597B4(void *stream, void *parent_stream, unsigned short mode) {
    short i;
    short slot;
    Channel *c;
    Channel *p;
    unsigned short flags;

    for (i = 0; i < 10; i++) {
        if (D_800E474C[i].flags == 0) {
            break;
        }
    }
    c = &D_800E474C[i];
    slot = i;
    c->sounds[0] = -1;
    c->sounds[1] = -1;
    c->sounds[2] = -1;
    c->sounds[3] = -1;
    c->sounds[4] = -1;
    c->sounds[5] = -1;
    c->stream = stream;
    c->flags = 0x80;
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
