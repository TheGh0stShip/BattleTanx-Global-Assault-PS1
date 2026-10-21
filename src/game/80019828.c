typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
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
    unsigned short id;
    Vector near;
    Vector far;
    short hit;
} Hit;
extern Cell D_800C62B0[];
extern unsigned short D_800C628C;
extern unsigned short D_800A436C;
extern unsigned short D_800C60F8[];
unsigned short func_800190CC(Vector *, Vector *, short, Vector *, Vector *);
unsigned short func_80017EE4(Pos2 *, Pos2 *, unsigned short, Pos2 *, Pos2 *);

static inline void set_pos2(Pos2 *p, int x, int z) {
    p->x = x;
    p->z = z;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void vec_copy(Vector *d, Vector *s) {
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

static inline int dist3(short ax, short bx, short ay, short by, short az, short bz) {
    int z = bz;
    return ax * bx + ay * by + az * z;
}

static inline int dist2(short ax, short bx, short az, short bz) {
    int z = bz;
    return ax * bx + az * z;
}

int func_80019828(Vector *from, Vector *to, unsigned short id, unsigned short slot, int mask, unsigned short grow,
                  void *ignore, Hit *out, unsigned int *best) {
    Vector delta;
    Vector p1;
    Vector p2;
    Pos2 a;
    Pos2 b;
    Pos2 q1;
    Pos2 q2;
    int fx;
    int fz;
    int tx;
    int tz;
    Cell *c;
    unsigned short hit;
    unsigned int dist;
    int result;
    unsigned short cur;

    result = 0;
    cur = id;
    while (cur != 0xFFFF) {
        c = &D_800C62B0[cur];
        if ((ignore == 0 || c->owner != ignore) && !(c->flags & 0x04000000) && (c->flags & mask)) {
            if (grow) {
                c->min_x -= grow;
                c->max_x += grow;
                c->min_z -= grow;
                c->max_z += grow;
            }
            if (D_800C628C) {
                hit = func_800190CC(from, to, cur, &p1, &p2);
            } else {
                set_pos2(&a, from->x, from->z);
                set_pos2(&b, to->x, to->z);
                set_pos2(&q1, p1.x, p1.z);
                set_pos2(&q2, p2.x, p2.z);
                hit = func_80017EE4(&a, &b, cur, &q1, &q2);
                from->x = a.x;
                from->z = a.z;
                to->x = b.x;
                to->z = b.z;
                p1.x = q1.x;
                p1.z = q1.z;
                p2.x = q2.x;
                p2.z = q2.z;
                p1.y = p2.y = 0;
            }
            if (grow) {
                c->min_x += grow;
                c->max_x -= grow;
                c->min_z += grow;
                c->max_z -= grow;
            }
            if (slot != 3) {
                D_800C62B0[cur].flags |= 0x04000000;
                D_800C60F8[D_800A436C] = cur;
                D_800A436C++;
            }
            if (hit) {
                result = 1;
                delta.x = from->x - p1.x;
                delta.z = from->z - p1.z;
                if (D_800C628C) {
                    delta.y = from->y - p1.y;
                    dist = dist3(to_int(delta.x) >> 2, to_int(delta.x) >> 2, to_int(delta.y) >> 2,
                                 to_int(delta.y) >> 2, to_int(delta.z) >> 2, to_int(delta.z) >> 2);
                } else {
                    dist = dist2(to_int(delta.x) >> 2, to_int(delta.x) >> 2, to_int(delta.z) >> 2,
                                 to_int(delta.z) >> 2);
                }
                if (dist < *best) {
                    *best = dist;
                    out->owner = c->owner;
                    out->id = cur;
                    vec_copy(&out->near, &p1);
                    vec_copy(&out->far, &p2);
                    out->hit = hit;
                }
            }
        }
        cur = c->next[slot];
    }
    return result;
}
