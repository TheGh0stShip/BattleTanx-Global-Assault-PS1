typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    short x;
    short z;
    short y;
    char pad16[0x28 - 0x16];
} Cell;
typedef struct Hit {
    void *owner;
    unsigned short id;
    char pad06[2];
    Vector pos;
    Vector normal;
    unsigned short depth;
    char pad22[2];
} Hit;
typedef struct Normal2 {
    int x;
    int z;
} Normal2;
extern Cell D_800C62B0[];
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
unsigned short func_80017760(unsigned short, unsigned short, Normal2 *, unsigned short *);

static inline void set_vec(Vector *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

unsigned short func_80017878(unsigned short self, unsigned short start, unsigned short slot, int mask, Hit *hits,
                             unsigned short count, unsigned short first_only) {
    unsigned short found = 0;
    unsigned short cur = start;
    Cell *e;
    Normal2 n;
    unsigned short depth;
    unsigned short i;
    Hit *h;

    while (cur != 0xFFFF) {
        e = &D_800C62B0[cur];
        if (cur != self && !(e->flags & 0x04000000) && (e->flags & mask)) {
            if (func_80017760(self, cur, &n, &depth)) {
                h = hits;
                for (i = 0; i < count + found; i++, h++) {
                    if (cur == h->id) {
                        break;
                    }
                }
                if (i >= count + found) {
                    h->owner = e->owner;
                    h->id = cur;
                    set_vec(&h->normal, n.x, 0, n.z);
                    h->depth = depth;
                    set_vec(&h->pos, e->x << 14, e->y << 14, e->z << 14);
                    found++;
                    if (first_only) {
                        return found;
                    }
                    if (count + found >= 8) {
                        break;
                    }
                }
            }
            if (slot != 3) {
                D_800C62B0[cur].flags |= 0x04000000;
                D_800C60F8[D_800A436C] = cur;
                D_800A436C++;
            }
        }
        cur = e->next[slot];
    }
    return found;
}
