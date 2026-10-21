typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point;
typedef struct { int pad; short type; } Entity;
typedef struct {
    Entity *obj;
    int pad;
    Vector pos;
    Vector normal;
    int extra;
} Hit;
typedef struct { char pad[7]; unsigned char team; } Owner;
typedef struct {
    int pad[2];
    Vector pos;
    Vector vel;
    int kind;
    int time;
    unsigned short spin;
    short pad2;
    int source;
    int pad3;
    Entity *ignore;
    Owner *owner;
} Shell;
extern int D_800D2FE0;
extern int D_800A47F4[];
extern int D_800A47E4[];
extern unsigned short D_800A47DC[];
extern int D_800DE30C;
extern short D_800C628C;
void func_8006FDB0(int, Vector *, int, int);
void func_80053790(int, int, int);
void func_800235E0(Vector *, int, int, int, int);
int func_80023B8C(Vector *, int, int, int, int, int);
void func_80054A30(int);
int func_8001EA3C(Point *);
unsigned int func_80086C84(void);
unsigned short func_80019D80(Vector *, Vector *, int, unsigned short, int, Hit *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8002ADA4(Shell *p, int *done) {
    int kind;
    int dt;
    Vector next;
    Point ground;
    Hit hit;
    Vector bounce;
    int dot;
    int fx;
    unsigned short reach;

    kind = p->kind;
    if (D_800D2FE0 - p->time > D_800A47F4[kind]) {
        p->pos.y -= D_800A47E4[kind];
        *done = 1;
        switch ((unsigned int)p->kind) {
        case 0:
            fx = 6;
            goto blast;
        case 3:
            func_8006FDB0(10, &p->pos, 0, func_80023B8C(&p->pos, p->owner->team, p->source, 99, 0, 9000));
            func_80054A30(28);
            break;
        case 2:
            func_8006FDB0(11, &p->pos, 0, func_80023B8C(&p->pos, p->owner->team, p->source, 97, 0, 9000));
            break;
        case 1:
            fx = 7;
        blast:
            func_8006FDB0(fx, &p->pos, 0, 0);
            func_80053790(12, p->pos.x, p->pos.z);
            func_800235E0(&p->pos, 172, p->source, p->owner->team, 0xE49D0A);
            break;
        }
        return;
    }
    dt = D_800DE30C;
    p->vel.y -= fixed_mul(8192, dt);
    ground.x = next.x = p->pos.x + fixed_mul(p->vel.x, dt);
    next.y = p->pos.y + fixed_mul(p->vel.y, dt);
    ground.z = next.z = p->pos.z + fixed_mul(p->vel.z, dt);
    if (next.y < func_8001EA3C(&ground) + D_800A47E4[p->kind]) {
        next.y = D_800A47E4[p->kind];
        p->vel.y = fixed_mul(-1638, p->vel.y);
        p->vel.x = fixed_mul(fixed_mul(func_80086C84() % 1638 + 3276, 2048), p->vel.x);
        p->vel.z = fixed_mul(fixed_mul(func_80086C84() % 1638 + 3276, 2048), p->vel.z);
        if (p->vel.y > 16384) {
            func_80053790(29, next.x, next.z);
        }
        if (kind != 3 && p->vel.y < 8192) {
            p->time = -1000;
        }
    }
    reach = D_800A47DC[kind];
    D_800C628C = 1;
    if (func_80019D80(&p->pos, &next, 0x64940B, reach, 0, &hit) != 0) {
        if (p->ignore != 0 && hit.obj == p->ignore) {
            p->pos.x = next.x;
            p->pos.y = next.y;
            p->pos.z = next.z;
        } else if (hit.obj->type == 4) {
            p->time = -1000;
        } else {
            {
                int vx = p->vel.x;
                dot = fixed_mul(hit.normal.x, vx) + fixed_mul(hit.normal.y, p->vel.y) + fixed_mul(hit.normal.z, p->vel.z);
            }
            bounce.x = p->vel.x - fixed_mul(dot, hit.normal.x) * 2;
            bounce.y = p->vel.y - fixed_mul(dot, hit.normal.y) * 2;
            bounce.z = p->vel.z - fixed_mul(dot, hit.normal.z) * 2;
            if ((bounce.y ^ p->vel.y) < 0 && bounce.y < 8192) {
                p->time = -1000;
            }
            p->pos.x = hit.pos.x + bounce.x;
            p->pos.y = hit.pos.y + bounce.y;
            p->pos.z = hit.pos.z + bounce.z;
            p->vel.x = fixed_mul(2457, bounce.x);
            p->vel.y = fixed_mul(2457, bounce.y);
            p->vel.z = fixed_mul(2457, bounce.z);
            p->ignore = 0;
        }
    } else {
        p->pos.x = next.x;
        p->pos.y = next.y;
        p->pos.z = next.z;
        p->ignore = 0;
    }
    p->spin += 512;
}
