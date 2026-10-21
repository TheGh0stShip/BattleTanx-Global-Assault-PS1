typedef struct { int x; int y; } Point;
typedef struct { char pad[34]; short angle; char pad2[4]; } Cell;

extern Cell D_800C62B0[];
extern void func_80016FF4(Cell *, Point *);
extern unsigned short func_80017EE4(Point *, Point *, int, Point *, Point *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int sat_square(int x, int mask) {
    int result;

    __asm__ volatile(".set\tnoreorder\n\tmult %1, %1\n\tmflo $2\n\tmfhi $3\n\tblez $3, 1f\n\tand $2, $3, %2\n\tbnez $2, 2f\n\tlui %0, 0x7fff\n"
                     "1:\tbgez $3, 3f\n\tnegu $2, $3\n\tand $2, $2, %2\n\tbeqz $2, 3f\n\tlui %0, 0x7fff\n"
                     "2:\tj 4f\n\tori %0, %0, 0xffff\n"
                     "3:\tsrl %0, %0, 12\n\tsll $3, $3, 20\n\tor %0, %0, $3\n4:\n\t.set\treorder"
                     : "=r"(result)
                     : "r"(x), "r"(mask)
                     : "$3", "memory");
    return result;
}

static inline void get_corners(int idx, Point *c) {
    func_80016FF4(&D_800C62B0[idx], c);
}

int func_8001C13C(int unused, unsigned short a, unsigned short b, Point *dir, Point *out) {
    Point offset;
    Point probe;
    Point hit;
    Point normal;
    Point corners[4];
    Point *p;
    int scale;
    int best;
    register int d asm("$3");
    int dx;
    int dy;
    int sq_x;
    register int sq_y asm("$2");
    int mask;

    {
        Cell *za = &D_800C62B0[a];
        Cell *zb = &D_800C62B0[b];
        scale = (za->angle + zb->angle) << 18 >> 2;
    }
    offset.x = fixed_mul(-dir->x, scale);
    offset.y = fixed_mul(-dir->y, scale);
    best = 0;
    get_corners(a, corners);
    for (p = corners, mask = -4096; p < &corners[4]; p++) {
        probe.x = p->x - offset.x;
        probe.y = p->y - offset.y;
        if (func_80017EE4(&probe, p, b, &hit, &normal)) {
            dx = p->x - hit.x;
            dy = p->y - hit.y;
            sq_x = sat_square(dx, mask);
            sq_y = sat_square(dy, mask);
            d = sq_x + sq_y;
            if (best < d) {
                out->x = p->x;
                out->y = p->y;
                best = d;
            }
        }
    }
    get_corners(b, corners);
    for (p = corners, mask = -4096; p < &corners[4]; p++) {
        probe.x = p->x + offset.x;
        probe.y = p->y + offset.y;
        if (func_80017EE4(&probe, p, a, &hit, &normal)) {
            dx = p->x - hit.x;
            dy = p->y - hit.y;
            sq_x = sat_square(dx, mask);
            sq_y = sat_square(dy, mask);
            d = sq_x + sq_y;
            if (best < d) {
                out->x = p->x;
                out->y = p->y;
                best = d;
            }
        }
    }
    return best;
}
