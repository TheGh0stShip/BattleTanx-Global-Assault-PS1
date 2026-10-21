typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } TrailPoint;
typedef struct { int pad; short type; } Entity;
typedef struct { Entity *obj; int pad; Vector pos; int nx; int solid; int nz; unsigned short kind; } Hit;
typedef struct { Vector pos; unsigned short angle; short pad; int team; int owner; int power; int pad2[2]; } HitMsg;
typedef struct { unsigned int code; int pad[6]; } Result;
typedef void (*Handler)(Entity *, void *, int, HitMsg *, Result *);
typedef struct { int pad; Handler handler; int pad2; } TypeInfo;
typedef struct {
    int pad[2];
    Vector pos;
    Vector vel;
    int spread;
    TrailPoint *trail;
    int life;
    unsigned short angle;
    unsigned char count;
    unsigned char index;
    unsigned char team;
    unsigned char power;
    short pad2;
    int id;
    int owner;
} Bolt;
extern int D_800DE30C;
extern short D_800C628C;
extern TypeInfo D_800D32F4[];
extern Result D_800BDB18;
void func_8002382C(TrailPoint *);
unsigned int func_80086C84(void);
unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
int func_8008AE30(int, int);
void func_80053790(int, int, int);
void func_8006FDB0(int, Vector *, int, int);
int func_800248CC(int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline short quarter(int v) {
    return (to_int(v) << 14) >> 16;
}

static inline void reflect(Bolt *b, Hit *hit) {
    Vector v;
    int dot;

    {
        int vx = b->vel.x;
        dot = fixed_mul(hit->nx, vx) + fixed_mul(hit->nz, b->vel.z);
    }
    v.x = b->vel.x - (fixed_mul(dot, hit->nx) << 1);
    v.y = b->vel.y;
    v.z = b->vel.z - (fixed_mul(dot, hit->nz) << 1);
    b->pos.x += v.x;
    b->pos.z += v.z;
    b->vel = v;
    b->angle = (func_8008AE30(v.x, v.z) & 0xFFF) << 4;
}

void func_8002D7A0(Bolt *self, int *done) {
    Bolt *b;
    Vector next;
    Hit hit;
    int spread;
    int half;
    int stop;
    int explode;
    int bounced;

    stop = 0;
    explode = 1;
    bounced = 0;
    b = self;
    if (--b->life <= 0) {
        *done = 1;
        if (b->trail != 0) {
            func_8002382C(b->trail);
        }
        return;
    }
    b->trail[b->index].x = b->pos.x;
    b->trail[b->index].z = b->pos.z;
    b->index = (b->index + 1) & 7;
    if (b->count < 8) {
        b->count++;
    }
    spread = fixed_mul(3276, b->spread);
    half = spread >> 1;
    next.x = b->pos.x + fixed_mul(func_80086C84() % spread - half + b->vel.x, D_800DE30C);
    next.z = b->pos.z + fixed_mul(func_80086C84() % spread - half + b->vel.z, D_800DE30C);
    D_800C628C = 1;
    next.y = b->pos.y;
    if (func_80019D80(&b->pos, &next, 0x64940B, 0, b->id, &hit) != 0) {
        hit.pos.y = b->pos.y;
        if (hit.obj != 0) {
            HitMsg msg;
            Result res;

            res = D_800BDB18;
            msg.pos = hit.pos;
            msg.angle = b->angle;
            msg.team = b->team;
            msg.owner = b->owner;
            msg.power = b->power;
            res.code = 5;
            if (D_800D32F4[hit.obj->type].handler != 0 && hit.obj->type != -1) {
                D_800D32F4[hit.obj->type].handler(hit.obj, b, 0, &msg, &res);
            }
            switch (res.code) {
            case 1:
                stop = 1;
                break;
            case 3:
                stop = 1;
                explode = 0;
                break;
            case 5:
            default:
                if (hit.solid == 0 && hit.kind != 7) {
                    reflect(b, &hit);
                    bounced = 1;
                } else {
                    stop = 1;
                }
                break;
            }
        } else if (hit.solid == 0 && hit.kind != 7) {
            reflect(b, &hit);
            bounced = 1;
        } else {
            stop = 1;
        }
    }
    if (stop) {
        b->life = -1;
        if (explode) {
            Vector spot;

            spot.y = hit.pos.y;
            spot.x = hit.pos.x + (b->pos.x - hit.pos.x) / 10;
            spot.z = hit.pos.z + (b->pos.z - hit.pos.z) / 10;
            func_80053790(31, b->pos.x, b->pos.z);
            func_8006FDB0(4, &spot, 0, 0);
        }
        return;
    }
    if (!bounced) {
        b->pos.x = next.x;
        b->pos.z = next.z;
    } else {
        switch ((int)((func_80086C84() >> 16) & 3)) {
        case 0:
            func_80053790(35, b->pos.x, b->pos.z);
            break;
        case 1:
            func_80053790(36, b->pos.x, b->pos.z);
            break;
        case 2:
            func_80053790(37, b->pos.x, b->pos.z);
            break;
        case 3:
            func_80053790(38, b->pos.x, b->pos.z);
            break;
        }
    }
    if (func_800248CC(quarter(next.x), quarter(next.z)) == 0) {
        b->life = -1;
    }
}
