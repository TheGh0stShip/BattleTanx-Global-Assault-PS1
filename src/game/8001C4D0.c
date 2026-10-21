typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;
typedef struct Hit {
    void *owner;
    unsigned short id;
    char pad06[0x20 - 6];
    unsigned short part;
    char pad22[0x24 - 0x22];
} Hit;
typedef struct Mover {
    int dx;
    int dz;
    char pad08[0x60 - 8];
    void *dir;
} Mover;
int func_8001EE10(int, int, int, int);
int func_8001EE5C(Pos2 *);
void func_8008AAD0(Vec3 *, Vec3 *);
void func_800169A8(short, short, unsigned short, Pos2 *);
int func_8001C13C(Mover *, unsigned short, unsigned short, Pos2 *, Pos2 *);
int func_8008ABF0(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void normalize2(Pos2 *v) {
    Vec3 t;
    int shift;
    int zero;

    shift = func_8001EE5C(v);
    if (shift != 0) {
        t.x = v->x >> shift;
        t.y = 0;
        t.z = v->z >> shift;
    } else {
        t.x = v->x;
        t.y = 0;
        t.z = v->z;
    }
    func_8008AAD0(&t, &t);
    v->x = t.x;
    v->z = t.z;
    zero = v->x == 0 && v->z == 0;
    if (zero) {
        v->z = 4096;
    }
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

int abs(int);

int func_8001C4D0(Mover *m, unsigned short id, Pos2 *moved, Pos2 *from, Hit *hits, unsigned short count,
                  void **owner, Pos2 *normal, unsigned short *part, short mode) {
    Pos2 tmp;
    Pos2 push;
    Pos2 avg;
    Pos2 pts[10];
    int dist = 0;
    Hit *hit = hits;
    unsigned short i;
    unsigned short n;
    unsigned short j;
    int best;

    if (mode == 0) {
        push.x = from->x - moved->x;
        push.z = from->z - moved->z;
        dist = func_8001EE10(push.x, push.z, 0, 0);
        if (dist != 0) {
            normalize2(&push);
        }
    }
    if (m->dir == 0) {
        n = 0;
        if (mode >= 0) {
            for (i = n; i < count; i++, hit++) {
                func_800169A8(to_int(from->x) >> 2, to_int(from->z) >> 2, hit->id, &pts[n]);
                for (j = 0; j < n; j++) {
                    if (pts[n].x == pts[j].x && pts[n].z == pts[j].z) {
                        break;
                    }
                    if (abs(pts[n].x + pts[j].x) < 4 && abs(pts[n].z + pts[j].z) < 4) {
                        return 1;
                    }
                }
                if (j >= n) {
                    n++;
                    if (n >= 10) {
                        return 1;
                    }
                }
            }
            avg.z = 0;
            avg.x = 0;
            for (i = 0; i < n; i++) {
                avg.x += pts[i].x;
                avg.z += pts[i].z;
            }
            if (n >= 2) {
                normalize2(&avg);
            }
            if (mode == 0 && dist >= 410 && n < 2) {
                if (fixed_mul(push.x, avg.x) + fixed_mul(push.z, avg.z) < 0) {
                    push.x = avg.x;
                    push.z = avg.z;
                }
            } else {
                push.x = avg.x;
                push.z = avg.z;
            }
        } else {
            push.x = -m->dx;
            push.z = -m->dz;
        }
    }
    *owner = 0;
    hit = hits;
    best = 0;
    for (i = 0; i < count; hit++, i++) {
        int d = func_8001C13C(m, id, hit->id, &push, &tmp);

        if (best < d) {
            *owner = hit->owner;
            normal->x = tmp.x;
            normal->z = tmp.z;
            *part = hit->part;
            best = d;
        }
    }
    if (best == 0) {
        return 0;
    }
    best = func_8008ABF0(best) + 0x8000;
    moved->x += fixed_mul(push.x, best);
    moved->z += fixed_mul(push.z, best);
    normal->x += fixed_mul(push.x, best);
    normal->z += fixed_mul(push.z, best);
    return 0;
}
