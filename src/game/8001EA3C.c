typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    short y;
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    short y_low;
    short y_high;
    short radius;
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
typedef struct Hit {
    void *owner;
    volatile unsigned short id;
    char pad06[0x24 - 6];
} Hit;
extern Cell D_800C62B0[];
unsigned short func_8001A638(void *, int, Hit *, int);
int func_8001DA70(unsigned short, void *);

int abs(int);

int func_8001EA3C(void *pos) {
    Hit hits[8];
    int best = -0x3E8000;
    unsigned short count;
    unsigned short i;
    Cell *e;
    int v;

    count = func_8001A638(pos, 224, hits, 0);
    for (i = 0; i < count; i++) {
        Hit *h = &hits[i];

        e = &D_800C62B0[h->id];
        switch (e->flags & 0xE0) {
        case 64:
            v = func_8001DA70(h->id, pos);
            break;
        case 32: {
            if (abs(e->y_low) > abs(e->y_high)) {
                v = (short)(e->y_low + e->y) << 14;
            } else {
                v = (short)(e->y_high + e->y) << 14;
            }
            break;
        }
        default:
            v = 0;
            break;
        }
        if (best < v) {
            best = v;
        }
    }
    if (best == -0x3E8000) {
        return 0;
    }
    return best;
}
