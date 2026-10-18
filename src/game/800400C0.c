typedef struct { int x; int y; int z; } Vector;
typedef struct { int x; int z; } Point;
typedef struct { char pad[0x10]; unsigned int flags; char pad2[0xD0 - 0x14]; } Vehicle;
typedef struct {
    int id;
    char pad0[4];
    Vector pos;
    char pad1[0x2C - 0x14];
    unsigned short heading;
    char pad2[0x34 - 0x2E];
    char effect[0x9C - 0x34];
    int type;
    char pad3[0x214 - 0xA0];
    int health;
    unsigned int status;
    char pad4[4];
    int vx;
    char pad5[4];
    int vz;
} Tank;
extern Vehicle D_800A4EF4[];
extern unsigned int func_80086C84(void);
extern int func_8008ACC0(int);
extern int func_8008AD60(int);
extern void func_80074254(int, Vector *, int, int);
extern void func_80054DF8(Tank *, int);
extern void func_8003FB68(Tank *, int, int, int);
extern void func_8001F170(void *, Point *, int, int, Point *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800400C0(Tank *t, int damage, int attacker, int unused, Vector *src, unsigned short heading, int kind)
{
    int facing;
    int dx;
    int dz;
    int push;
    int angle;
    Point from;
    Point to;

    if (t->health > 0) {
        func_80074254(t->id, src, damage, kind);
        func_80054DF8(t, 39);
        t->health -= damage;
        if (t->health > 0) {
            return;
        }
        damage += t->health;
    }
    if (D_800A4EF4[t->type].flags & 0x20) {
        dx = src->x - t->pos.x;
        facing = fixed_mul(func_8008AD60(t->heading >> 4), dx);
        dz = src->z - t->pos.z;
        facing += fixed_mul(func_8008ACC0(t->heading >> 4), dz);
        if (facing > 0) {
            if (t->status & 2) {
                func_8003FB68(t, damage / 4, attacker, 0);
            } else {
                func_8003FB68(t, damage / 8, attacker, 0);
            }
            return;
        }
    }
    func_8003FB68(t, damage, attacker, 0);
    push = (damage << 11) / 30;
    push = fixed_mul(((func_80086C84() >> 16) * 3277 >> 16) + 1638, push);
    angle = heading >> 4;
    t->vx += fixed_mul(func_8008ACC0(angle), push);
    t->vz -= fixed_mul(func_8008AD60(angle), push);
    from.x = t->pos.x;
    from.z = t->pos.z;
    to.x = src->x;
    to.z = src->z;
    func_8001F170(t->effect, &from, damage * 5 << 16, heading, &to);
}
