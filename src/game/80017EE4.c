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
    short radius;
    unsigned short angle;
} Cell;
extern Cell D_800C62B0[];
extern int func_80016D78(int, int, unsigned short);
void func_800167D0(Pos2 *, unsigned short, Pos2 *);

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
    register int n_zeros asm("$4");
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

static inline int sine_lookup(int angle) {
    int value;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9");
    return value;
}

static inline int cosine_lookup(int angle) {
    int value;

    __asm__ volatile("addiu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9", "$10");
    return value;
}


static inline void set_pos2(Pos2 *p, int x, int z) {
    p->x = x;
    p->z = z;
}

static inline void pos2_copy(Pos2 *r, Pos2 *a) {
    r->x = a->x;
    r->z = a->z;
}

static inline void pos2_sub(Pos2 *r, Pos2 *a, Pos2 *b) {
    int x = a->x - b->x;
    int z = a->z - b->z;

    r->x = x;
    r->z = z;
}

static inline int pos2_is_zero(Pos2 *v) {
    return v->x == 0 && v->z == 0;
}

int func_80017EE4(Pos2 *a, Pos2 *b, unsigned short id, Pos2 *out, Pos2 *normal) {
    Pos2 delta;
    Pos2 p0;
    Pos2 p1;
    Pos2 d;
    Pos2 tmp;
    Cell *e;
    int s;
    int c;
    int t;
    int v;
    int den;
    int num;
    int hx;
    register int hm asm("$2");
    int hz;
    unsigned short angle;

    pos2_sub(&delta, b, a);
    if (pos2_is_zero(&delta)) {
        if ((unsigned short)func_80016D78((short)(to_int(a->x) >> 2), (short)(to_int(a->z) >> 2), id)) {
            goto inside;
        }
        return 0;
    }
    e = &D_800C62B0[id];
    angle = e->angle;
    if (angle == 0) {
        s = 0;
        c = 4096;
        set_pos2(&p0, a->x - (e->x << 14), a->z - (e->z << 14));
        pos2_copy(&d, &delta);
        set_pos2(&p1, b->x - (e->x << 14), b->z - (e->z << 14));
    } else {
        s = sine_lookup(angle) >> 4;
        c = cosine_lookup(angle) >> 4;
        set_pos2(&tmp, a->x - (e->x << 14), a->z - (e->z << 14));
        func_800167D0(&tmp, e->angle, &p0);
        func_800167D0(&delta, e->angle, &d);
        set_pos2(&p1, p0.x + d.x, p0.z + d.z);
    }
    if (p0.x < e->min_x << 14) {
        if (p1.x < e->min_x << 14) {
            return 0;
        }
        do {
            if (p0.z < e->min_z << 14) {
                if (p1.z < e->min_z << 14) {
                    return 0;
                }
                num = (e->min_z << 14) - p0.z;
                den = d.z;
                if (den == 0) {
                    den = 2;
                }
                t = fixed_div(num, den);
                v = p0.x + fixed_mul(d.x, t);
                if (v >= e->min_x << 14 && v <= e->max_x << 14) {
                    hm = fixed_mul(delta.x, t);
                    hx = a->x;
                    hx += hm;
                    hz = fixed_mul(delta.z, t);
                    set_pos2(out, hx, a->z + hz);
                    normal->x = -s;
                    normal->z = -c;
                    return 2;
                }
            } else if (p0.z > e->max_z << 14) {
                if (p1.z > e->max_z << 14) {
                    return 0;
                }
                num = (e->max_z << 14) - p0.z;
                den = d.z;
                if (den == 0) {
                    den = 2;
                }
                t = fixed_div(num, den);
                v = p0.x + fixed_mul(d.x, t);
                if (v >= e->min_x << 14 && v <= e->max_x << 14) {
                    goto hit_max_z;
                }
            }
            num = (e->min_x << 14) - p0.x;
            den = d.x;
            if (den == 0) {
                den = 2;
            }
        } while (0);
        t = fixed_div(num, den);
        v = p0.z + fixed_mul(d.z, t);
        if (v < e->min_z << 14 || v > e->max_z << 14) {
            return 0;
        }
        hm = fixed_mul(delta.x, t);
        hx = a->x;
        hx += hm;
        hz = fixed_mul(delta.z, t);
        set_pos2(out, hx, a->z + hz);
        set_pos2(normal, -c, s);
        return 4;
    }
    if (p0.x > e->max_x << 14) {
        if (p1.x > e->max_x << 14) {
            return 0;
        }
        if (p0.z < e->min_z << 14) {
            if (p1.z < e->min_z << 14) {
                return 0;
            }
            num = (e->min_z << 14) - p0.z;
            den = d.z;
            if (den == 0) {
                den = 2;
            }
            t = fixed_div(num, den);
            v = p0.x + fixed_mul(d.x, t);
            if (v >= e->min_x << 14 && v <= e->max_x << 14) {
                hm = fixed_mul(delta.x, t);
                hx = a->x;
                hx += hm;
                hz = fixed_mul(delta.z, t);
                set_pos2(out, hx, a->z + hz);
                normal->x = -s;
                normal->z = -c;
                return 2;
            }
        } else if (p0.z > e->max_z << 14) {
            if (p1.z > e->max_z << 14) {
                return 0;
            }
            num = (e->max_z << 14) - p0.z;
            den = d.z;
            if (den == 0) {
                den = 2;
            }
            t = fixed_div(num, den);
            v = p0.x + fixed_mul(d.x, t);
            if (v >= e->min_x << 14 && v <= e->max_x << 14) {
                goto hit_max_z;
            }
        }
        num = (e->max_x << 14) - p0.x;
        den = d.x;
        if (den == 0) {
            den = 2;
        }
        t = fixed_div(num, den);
        v = p0.z + fixed_mul(d.z, t);
        if (v < e->min_z << 14 || v > e->max_z << 14) {
            return 0;
        }
        hm = fixed_mul(delta.x, t);
        hx = a->x;
        hx += hm;
        hz = fixed_mul(delta.z, t);
        set_pos2(out, hx, a->z + hz);
        set_pos2(normal, c, -s);
        return 3;
    }
    do {
        if (p0.z < e->min_z << 14) {
            if (p1.z < e->min_z << 14) {
                return 0;
            }
            num = (e->min_z << 14) - p0.z;
            den = d.z;
            if (den == 0) {
                den = 2;
            }
            t = fixed_div(num, den);
            v = p0.x + fixed_mul(d.x, t);
            if (v < e->min_x << 14 || v > e->max_x << 14) {
                return 0;
            }
            hm = fixed_mul(delta.x, t);
            hx = a->x;
            hx += hm;
            hz = fixed_mul(delta.z, t);
            set_pos2(out, hx, a->z + hz);
            set_pos2(normal, -s, -c);
            return 2;
        }
    } while (0);
    if (p0.z > e->max_z << 14) {
        if (p1.z > e->max_z << 14) {
            return 0;
        }
        num = (e->max_z << 14) - p0.z;
        den = d.z;
        if (den == 0) {
            den = 2;
        }
        t = fixed_div(num, den);
        v = p0.x + fixed_mul(d.x, t);
        if (v < e->min_x << 14 || v > e->max_x << 14) {
            return 0;
        }
    hit_max_z:
        hm = fixed_mul(delta.x, t);
        hx = a->x;
        hx += hm;
        hz = fixed_mul(delta.z, t);
        set_pos2(out, hx, a->z + hz);
        set_pos2(normal, s, c);
        return 1;
    }
inside:
    set_pos2(out, a->x, a->z);
    set_pos2(normal, 0, 4096);
    return 7;
}
