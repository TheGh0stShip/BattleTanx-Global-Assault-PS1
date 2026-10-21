typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Pos2;
typedef struct Cell {
    int head;
    char pad04[4];
    unsigned short next[4];
    short x;
    short z;
    short y;
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    short min_y;
    short max_y;
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
extern Cell D_800C62B0[];
extern int func_80016D78(int, int, unsigned short);
extern int func_80017EE4(Pos2 *, Pos2 *, unsigned short, Pos2 *, Pos2 *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

int abs(int);

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        quotient = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = quotient / (d >> scale);
            } else {
                quotient = quotient / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = quotient / (d >> -excess);
        }
    } else {
        quotient = n << 12;
        quotient = quotient / d;
    }
    result = quotient;
    if (negative) {
        return -result;
    }
    return result;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline int point_in_cell(Vector *p, unsigned short id) {
    short x = to_int(p->x) >> 2;
    short z = to_int(p->z) >> 2;
    int y = (short)(to_int(p->y) >> 2);
    Cell *e = &D_800C62B0[id];
    int r;

    if (y >= e->y + e->min_y && y <= e->y + e->max_y) {
        r = func_80016D78(x, z, id);
    } else {
        r = 0;
    }
    return r;
}

static inline void vec_sub(Vector *r, Vector *a, Vector *b) {
    r->x = a->x - b->x;
    r->y = a->y - b->y;
    r->z = a->z - b->z;
}

static inline void set_pos2(Pos2 *p, int x, int z) {
    p->x = x;
    p->z = z;
}

static inline int is_zero(Vector *v) {
    return v->x == 0 && v->y == 0 && v->z == 0;
}

int func_800190CC(Vector *a, Vector *b, short id, Vector *out, Vector *normal)
{
    Vector d;
    Vector p;
    Pos2 pa;
    Pos2 pb;
    Pos2 po;
    Pos2 pn;
    Cell *e;
    int top;
    int bottom;
    int limit;
    int scale;
    int y;
    unsigned short hit;

    vec_sub(&d, a, b);
    if (is_zero(&d)) {
        if ((unsigned short)point_in_cell(a, id)) {
            return 7;
        }
        return 0;
    }
    e = &D_800C62B0[id];
    normal->y = 0;
    top = (short)(e->y + e->max_y) << 14;
    bottom = (short)(e->y + e->min_y) << 14;
    y = a->y;
    if (y > top && b->y > top) {
        return 0;
    }
    if (y < bottom && b->y < bottom) {
        return 0;
    }
    set_pos2(&pa, a->x, a->z);
    set_pos2(&pb, b->x, b->z);
    set_pos2(&po, out->x, out->z);
    set_pos2(&pn, normal->x, normal->z);
    hit = func_80017EE4(&pa, &pb, id, &po, &pn);
    a->x = pa.x;
    a->z = pa.z;
    b->x = pb.x;
    b->z = pb.z;
    out->x = po.x;
    out->z = po.z;
    normal->x = pn.x;
    normal->z = pn.z;
    if (hit != 0) {
        if (d.x == 0) {
            p.y = a->y;
        } else {
            scale = fixed_div(out->x - a->x, d.x);
            p.y = a->y + fixed_mul(d.y, scale);
        }
        if (p.y >= bottom && p.y <= top) {
            out->y = p.y;
            return hit;
        }
        if (p.y > top) {
            limit = top;
        } else {
            limit = bottom;
        }
        if (d.y == 0) {
            p.x = a->y;
            p.z = a->z;
        } else {
            scale = fixed_div(limit - a->y, d.y);
            p.x = a->x + fixed_mul(d.x, scale);
            p.z = a->z + fixed_mul(d.z, scale);
        }
        if ((short)(to_int(p.x) >> 2) <= e->x + e->min_x) {
            return 0;
        }
        if ((short)(to_int(p.x) >> 2) >= e->x + e->max_x) {
            return 0;
        }
        if ((short)(to_int(p.z) >> 2) <= e->z + e->min_z) {
            return 0;
        }
        if ((short)(to_int(p.z) >> 2) >= e->z + e->max_z) {
            return 0;
        }
        out->x = p.x;
        out->y = p.y;
        out->z = p.z;
        if (limit == top) {
            normal->x = 0;
            normal->y = 4096;
            normal->z = 0;
            return 5;
        }
        normal->x = 0;
        normal->y = -4096;
        normal->z = 0;
        return 6;
    }
    return 0;
}
