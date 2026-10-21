typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;
typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    short x;
    short z;
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
typedef struct Node {
    short id;
    short next;
    short kind;
    short pad06;
    void *object;
} Node;
typedef struct Hit {
    Node *owner;
    unsigned short id;
    char pad06[0x20 - 6];
    unsigned short part;
    char pad22[0x24 - 0x22];
} Hit;
typedef struct Body {
    char pad00[0x208];
    void *owner;
    char pad20C[0x218 - 0x20C];
    int status;
} Body;
typedef struct Driver {
    short id;
    char pad02[6];
    Body *body;
} Driver;
typedef struct Mover {
    int dx;
    int dz;
    int speed;
    int length;
    char pad10[0x14 - 0x10];
    int drag;
    char pad18[0x5C - 0x18];
    unsigned char flags;
    char pad5D[0x60 - 0x5D];
    void *dir;
} Mover;
typedef struct Owned {
    char pad00[8];
    Node *node;
    char pad0C[0x3C - 0x0C];
    int side;
} Owned;
typedef struct Impact {
    Vec3 pos;
    unsigned short heading;
    short pad;
    int source;
    void *owner;
    int status;
    unsigned short part;
    short pad2;
    Mover *mover;
} Impact;
typedef struct Reply {
    int kind;
    char pad[0x1C - 4];
} Reply;
typedef struct NodeClass {
    void (*update)();
    void (*query)(Node *, Driver *, int, Impact *, Reply *);
    void (*draw)();
} NodeClass;
extern unsigned short D_800A437A;
extern int D_800DE30C;
extern Cell D_800C62B0[];
extern short D_800C628C;
extern NodeClass D_800D32F4[];
void func_8001B850(Mover *, int, unsigned short);
void func_8001BB58(Mover *, Pos2 *);
int func_8001EE10(int, int, int, int);
int func_8001EE5C(Pos2 *);
void func_8008AAD0(Vec3 *, Vec3 *);
void func_80015F64(unsigned short, short, short);
unsigned short func_80017AAC(unsigned short, int, Hit *, int, int);
Node *func_80031374(Owned *);
void func_8003FB68(Body *, int, int, int);
unsigned short func_8001C4D0(Mover *, unsigned short, Pos2 *, Pos2 *, Hit *, unsigned short, Node **, Pos2 *,
                             unsigned short *, short);
void func_80043D30(Body *, Reply *);
void func_80047A34(Body *, int, Node *);

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
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int safe_div(int num, int den) {
    if (den == 0) {
        den = 2;
    }
    return fixed_div(num, den);
}

static inline void normalize2(Pos2 *v, Vec3 *tp) {
    int shift;
    int zero;

    shift = func_8001EE5C(v);
    if (shift != 0) {
        tp->x = v->x >> shift;
        tp->y = 0;
        tp->z = v->z >> shift;
    } else {
        tp->x = v->x;
        tp->y = 0;
        tp->z = v->z;
    }
    func_8008AAD0(tp, tp);
    v->x = tp->x;
    v->z = tp->z;
    zero = v->x == 0 && v->z == 0;
    if (zero) {
        v->z = 4096;
    }
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline int to_int_n(int v) {
    return v < 0 ? -(-v >> 12) : v >> 12;
}

static inline void span(unsigned short *out, short lo, short hi) {
    if (hi - lo < 0) {
        *out = lo - hi;
    } else {
        *out = hi - lo;
    }
}

static inline unsigned short hits_owned(Hit *hits, unsigned short count) {
    unsigned short found = 0;
    unsigned short k;
    Hit *hit = hits;

    for (k = 0; k < count; hit++, k++) {
        if (D_800C62B0[hit->id].flags == 0x200000) {
            Owned *o = hit->owner->object;

            if (func_80031374(o) == hit->owner) {
                if (o->side < 0) {
                    if (hit->part == 2) {
                        found = 1;
                    }
                } else if (hit->part == 1) {
                    found = 1;
                }
            }
        }
    }
    return found;
}

static inline void span_ge(unsigned short *out, short lo, short hi) {
    unsigned short d;

    if (hi - lo >= 0) {
        d = hi - lo;
    } else {
        d = lo - hi;
    }
    *out = d;
}

static inline void place(unsigned short id, unsigned short angle, short x, short z) {
    if (id != 0xFFFF) {
        int off = id * sizeof(Cell);

        ((Cell *)((char *)D_800C62B0 + off))->angle = angle;
        func_80015F64(id, x, z);
    }
}

static inline unsigned short probe(unsigned short id, Hit *hits) {
    D_800C628C = 1;
    return func_80017AAC(id, 0xE45C0F, hits, 0, 0);
}

int func_8001CAC8(Mover *m, int arg1, unsigned short angle, Pos2 *pos, Pos2 *prev, unsigned short id,
                  Driver *drv, short *flag) {
    Pos2 cur;
    Pos2 p;
    Pos2 step;
    Pos2 normal;
    Impact imp;
    Reply reply;
    Hit hits[8];
    Vec3 t;
    unsigned short ex;
    unsigned short ez;
    Node *owner;
    unsigned short part;
    int drv_id = drv->id;
    int dist;
    int stepping;
    int travel;
    unsigned short n;
    unsigned short w;

    if (flag != 0) {
        *flag = 0;
    }
    if (D_800A437A != 0 || (m->flags & 0xF)) {
        if (m->speed > 0) {
            int dec = fixed_mul(D_800DE30C, m->drag);

            if (dec > 0) {
                m->speed -= dec;
                if (m->speed < 0) {
                    m->speed = 0;
                }
            }
        }
        func_8001B850(m, arg1, angle);
    }
    cur.x = pos->x;
    cur.z = pos->z;
    func_8001BB58(m, &cur);
    if (m->dir != 0) {
        goto done;
    }
    p.x = prev->x;
    p.z = prev->z;
    {
        Cell *c = &D_800C62B0[id];

        unsigned short *e0 = &ex;
        unsigned short *e1 = &ez;
        span_ge(e0, c->min_x, c->max_x);
        span(e1, c->min_z, c->max_z);
    }
    w = ez;
    if ((short)ez > (short)ex) {
        w = ex;
    }
    stepping = ((short)w >> 1 << 14) - 4096;
    step.x = cur.x - p.x;
    step.z = cur.z - p.z;
    if (step.x == 0 && step.z == 0) {
        dist = 0;
    } else {
        dist = func_8001EE10(step.x, step.z, 0, 0);
        normalize2(&step, &t);
    }
    step.x = fixed_mul(stepping, step.x);
    step.z = fixed_mul(stepping, step.z);
    travel = 0;
    do {
        travel += stepping;
        if (travel < dist) {
            p.x += step.x;
            p.z += step.z;
        } else {
            p.x = cur.x;
            p.z = cur.z;
        }
        {
            short gx = to_int_n(p.x) >> 2;
            int gz = (short)(to_int(p.z) >> 2);

            place(id, angle, gx, gz);
        }
        n = probe(id, hits);
    } while (travel < dist && n == 0);
    if (n == 0) {
        goto done;
    }
    if (flag != 0) {
        *flag = 16;
    }
    if (hits_owned(hits, n)) {
        if (drv->body != 0) {
            func_8003FB68(drv->body, 30000, 0, 1);
        }
        return 1;
    }
    if (func_8001C4D0(m, id, &p, prev, hits, n, &owner, &normal, &part, 0)) {
        pos->x = prev->x;
        pos->z = prev->z;
        return 1;
    }
    func_80015F64(id, (short)(to_int(p.x) >> 2), (short)(to_int(p.z) >> 2));
    n = probe(id, hits);
    if (n != 0) {
        if (hits_owned(hits, n)) {
            if (drv->body != 0) {
                func_8003FB68(drv->body, 30000, 0, 1);
            }
            return 1;
        }
        p.x = pos->x;
        p.z = pos->z;
        func_80015F64(id, (short)(to_int(p.x) >> 2), (short)(to_int(p.z) >> 2));
        n = probe(id, hits);
        if (n != 0) {
            if (hits_owned(hits, n)) {
                if (drv->body != 0) {
                    func_8003FB68(drv->body, 30000, 0, 1);
                }
                return 1;
            }
            if (func_8001C4D0(m, id, &p, prev, hits, n, &owner, &normal, &part, 1)) {
                pos->x = prev->x;
                pos->z = prev->z;
                return 1;
            }
            func_80015F64(id, (short)(to_int(p.x) >> 2), (short)(to_int(p.z) >> 2));
            n = probe(id, hits);
            if (n != 0) {
                if (hits_owned(hits, n)) {
                    if (drv->body != 0) {
                        func_8003FB68(drv->body, 30000, 0, 1);
                    }
                }
                pos->x = prev->x;
                pos->z = prev->z;
                return 1;
            }
        }
    }
    pos->x = p.x;
    pos->z = p.z;
    if (owner != 0) {
        Body *b = drv->body;

        reply.kind = 2;
        imp.pos.x = normal.x;
        imp.pos.y = 0;
        imp.pos.z = normal.z;
        imp.heading = angle;
        imp.mover = m;
        imp.source = 0;
        imp.part = part;
        if (b != 0) {
            imp.owner = b->owner;
            imp.status = b->status & 2;
        } else {
            imp.owner = 0;
            imp.status = 0;
        }
        if (D_800D32F4[owner->kind].query != 0 && owner->kind != -1) {
            D_800D32F4[owner->kind].query(owner, drv, 0, &imp, &reply);
        }
        b = drv->body;
        if (b != 0) {
            func_80043D30(b, &reply);
        }
    } else {
        reply.kind = 8;
        if (drv->body != 0) {
            func_80043D30(drv->body, &reply);
        }
    }
    if (drv_id == drv->id && drv->body != 0) {
        func_80047A34(drv->body, safe_div(m->speed, m->length), owner);
    }
    m->speed = fixed_mul(-2703, m->speed);
    if (m->speed < 0) {
        int t = -m->dx;

        m->dx = t;
        m->dz = -m->dz;
        m->speed = -m->speed;
    }
    if (pos->x - prev->x >= 0) {
        if (pos->x - prev->x < 16384) {
            goto okx;
        }
        goto out;
    }
    if (prev->x - pos->x >= 16384) {
        goto out;
    }
okx:
    if (pos->z - prev->z >= 0) {
        if (pos->z - prev->z < 16384) {
            goto okz;
        }
        goto out;
    }
    if (prev->z - pos->z >= 16384) {
        goto out;
    }
okz:
    pos->x = prev->x;
    pos->z = prev->z;
out:
    return 0;
done:
    pos->x = cur.x;
    pos->z = cur.z;
    return 0;
}
