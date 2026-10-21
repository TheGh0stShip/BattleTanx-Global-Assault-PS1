typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    Matrix m;
    unsigned char hit;
} TouchInfo;

typedef struct Node {
    short id;
    short next;
    short kind;
} Node;

typedef struct NodeClass {
    void (*update)();
    void (*touch)();
    void (*draw)();
} NodeClass;

typedef struct {
    char pad0[0xC];
    int team;
    char pad10[0x114 - 0x10];
} Waypoint;

typedef struct {
    char pad0[0x62];
    unsigned char sx;
    unsigned char sz;
} Map;

typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7;
    Vector pos;
    unsigned short angle;
    char pad16[3];
    unsigned char state;
    char pad1A[2];
    unsigned char armed;
    unsigned char owner;
    char pad1E[2];
    char pad20[4];
    unsigned short cell;
    char pad26[2];
    int timer;
    char pad2C[8];
    int t34;
    int health;
    Node *node;
} Turret;

typedef struct {
    int x;
    int z;
    int range;
    int team;
    int kind;
    int power;
} Blast;

extern NodeClass D_800D32F4[];
extern Waypoint D_800E3E68[];
extern Map *D_800D3024;
extern unsigned char D_800D2FEC;
extern int D_800D2FE0;
extern int D_800D2F50;
extern void func_8008A65C(Matrix *, Vector *, Vector *);
extern void func_80015F64(int, int, int);
extern int func_8004784C(int, int, int, int, int *);
extern int func_80024114(int, int);
extern void func_80029308(Turret *, int, Waypoint *);
extern int func_8008AE30(int, int);
extern void func_80035948(int, Vector *, int, int, int, int, int, int);

static inline void matrix_identity(Matrix *m) {
    __asm__ volatile("li $8, 4096\n\tsw $8, 0(%0)\n\tsw $0, 4(%0)\n\tsw $8, 8(%0)\n\tsw $0, 12(%0)\n\tsw $8, 16(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     : : "r"(m) : "$8", "memory");
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline void turret_capture(Turret *t, Vector *src, int dist, int team, int range) {
    int delay;

    delay = 0;
    if (t->owner != 127 && waypoint_get(t->owner)->team == waypoint_get(team)->team) {
        return;
    }
    if (func_8004784C(D_800D3024->sx, D_800D3024->sz, dist, range, &delay)) {
        t->owner = team;
        t->t34 = 0;
        t->state = 0;
    } else {
        Vector aim;

        aim.x = src->x;
        aim.y = src->y + 0x1E000;
        aim.z = src->z;
        t->state = 3;
        t->t34 = 0;
        t->timer = D_800D2FE0 + delay;
    }
}

void func_8002952C(Turret *t, void *msg, Blast *b) {
    Vector pos;
    int dx;
    int dz;
    int dist;
    int damage;
    Waypoint *w;

    if (b->kind == 1) {
        if (t->node != 0) {
            {
                int pair[2];
                TouchInfo info;
                TouchInfo *ip;
                NodeClass *cls;
                Vector *out;

                out = &pos;

                ip = &info;
                matrix_identity(&ip->m);
                pair[0] = 0;
                pair[1] = 0;
                info.hit = 0;
                cls = D_800D32F4;
                cls += t->node->kind;
                if (cls->touch != 0 && t->node->kind != -1) {
                    cls->touch(t->node, t, 1, pair, ip);
                }
                func_8008A65C(&info.m, &t->pos, out);
                func_80015F64(t->cell, (short)out->x, (short)out->z);
            }
        } else {
            pos = t->pos;
        }
        dx = fixed_to_int(b->x - pos.x);
        dz = fixed_to_int(b->z - pos.z);
        dist = dx * dx + dz * dz;
        turret_capture(t, &pos, dist, b->team, b->range);
    } else if (t->armed != 0) {
        damage = func_80024114(b->power, b->range);
        if (damage > 0) {
            if (b->team < D_800D2FEC && b->team != 127) {
                w = &D_800E3E68[b->team];
            } else {
                w = 0;
            }
            func_80029308(t, damage, w);
            if (t->health <= 0) {
                func_8008AE30(b->x - t->pos.z, b->x - t->pos.x);
                func_80035948(D_800D2F50, &t->pos, t->angle, 0, 0, 0, 0, 0);
                t->flags |= 2;
            }
        }
    }
}
