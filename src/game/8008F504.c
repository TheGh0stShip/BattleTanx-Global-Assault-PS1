extern void func_8008F4B4(int);
extern void func_8008F368(int);

typedef struct {
    char pad0[4];
    int flags;
    char pad8[12];
    unsigned int low_water;
    char pad24[4];
    unsigned char *ring;
    unsigned int size;
    unsigned int head;
    unsigned int count;
    int direct;
    char pad48[4];
    unsigned char *dbuf;
    unsigned int dlen;
    unsigned int dpos;
} S8008F504;
extern S8008F504 D_800EEDF4;

void func_8008F504(unsigned char c) {
    S8008F504 *s = &D_800EEDF4;
    unsigned int idx;

    if (s->flags & 0xF) {
        return;
    }
    if (s->direct != 0) {
        s->dbuf[s->dpos++] = c;
        if (s->dpos >= s->dlen) {
            func_8008F4B4(1);
        }
        return;
    }
    if (s->ring != 0 && s->count < s->size) {
        idx = s->head + s->count;
        if (idx > s->size) {
            idx -= s->size;
        }
        s->ring[idx] = c;
        s->count++;
        if (s->flags & 0x10) {
            if (s->size - s->count < s->low_water) {
                func_8008F368(0);
            }
        }
        return;
    }
    D_800EEDF4.flags |= 2;
}
