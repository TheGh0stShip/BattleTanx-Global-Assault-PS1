typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    char pad10[0x28 - 0x10];
} Cell;
typedef struct Hit {
    void *owner;
    unsigned short id;
    char pad06[0x24 - 6];
} Hit;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
extern Cell D_800C62B0[];
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
int func_80016D78(int, int, unsigned short);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

unsigned short func_8001A40C(Pos2 *pos, unsigned short start, unsigned short slot, int mask, Hit *hits,
                             unsigned short count, unsigned short first_only) {
    unsigned short found = 0;
    unsigned short cur = start;
    Cell *e;
    unsigned short i;
    Hit *h;

    while (cur != 0xFFFF) {
        e = &D_800C62B0[cur];
        if (!(e->flags & 0x04000000) && (e->flags & mask)) {
            if ((unsigned short)func_80016D78((short)(to_int(pos->x) >> 2), (short)(to_int(pos->z) >> 2), cur)) {
                h = hits;
                for (i = 0; i < count + found; i++, h++) {
                    if (cur == h->id) {
                        break;
                    }
                }
                if (i >= count + found) {
                    h->owner = e->owner;
                    h->id = cur;
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
