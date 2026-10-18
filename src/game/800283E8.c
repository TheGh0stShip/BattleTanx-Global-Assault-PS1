typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[0xC];
    int team;
} Owner;

typedef struct {
    char pad0[8];
    Vector pos;
    char pad14[0x208 - 0x14];
    Owner *owner;
} Tank;

typedef struct {
    unsigned short id;
    unsigned short next;
    char pad4[4];
    Tank *tank;
    char pad0C[0x40 - 0xC];
} Node;

extern Node *D_800D3258;
extern unsigned short D_800D3268;
extern int func_80047688(Tank *);
extern int func_8008AE30(int, int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

Tank *func_800283E8(Vector *from, int team) {
    int best = 0x7FFFFFFF;
    Tank *found = 0;
    short id;

    for (id = D_800D3268; id != -1; id = D_800D3258[id].next) {
        Tank *tank = D_800D3258[id].tank;

        if (tank != 0 && tank->owner->team != team && func_80047688(tank)) {
            int dx = tank->pos.x - from->x;
            int dz = tank->pos.z - from->z;
            int angle = func_8008AE30(dx, dz) & 0xFFF;
            int dist = fixed_mul(func_8008AD60(angle), dx);

            dist += fixed_mul(func_8008ACC0(angle), dz);
            if (dist < best) {
                best = dist;
                found = tank;
            }
        }
    }
    if (best <= 0x20CFFFF) {
        return found;
    }
    return 0;
}
