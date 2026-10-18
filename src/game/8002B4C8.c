typedef struct { int x, y, z; } Vector;
typedef struct {
    int pad[2];
    Vector pos;
    int vx;
    int speed;
    int vz;
    int kind;
    int time;
    unsigned short angle;
    short pad2;
    int owner;
    unsigned char team;
    char pad3[3];
    int arg52;
    int arg56;
} Shot;
extern int D_800D2FE0;
extern int D_800A47CC[];
extern int D_800A47BC[];
Shot *func_800237D0(int, int);
int func_8008AD60(int);
int func_8008ACC0(int);
void func_80054A30(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8002B4C8(Vector *pos, unsigned short angle, int owner, int kind, int arg52, unsigned char team, int arg56) {
    Shot *s;
    int t;

    s = func_800237D0(38, 60);
    if (s != 0) {
        s->team = team;
        s->kind = kind;
        s->pos.x = pos->x;
        s->pos.y = pos->y;
        s->pos.z = pos->z;
        s->owner = owner;
        s->time = D_800D2FE0;
        s->arg56 = arg56;
        s->arg52 = arg52;
        s->speed = D_800A47CC[kind];
        t = func_8008AD60(angle >> 4);
        s->vx = fixed_mul(D_800A47BC[kind], t);
        t = func_8008ACC0(angle >> 4);
        s->vz = fixed_mul(D_800A47BC[kind], t);
        s->angle = angle;
        if (s->kind == 3) {
            func_80054A30(30);
        }
    }
}
