typedef struct { short id; } Header;
typedef struct { Header *header; } Owner;
typedef struct {
    int pad[2];
    Owner *owner;
    int id;
    unsigned short rx, ry, rz;
    unsigned short vx, vy, vz;
    int start_time;
} Spinner;
extern int D_800D2FE0;
extern int D_800DE30C;

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80034670(Spinner *s, int *done) {
    if (D_800D2FE0 - s->start_time > 50) {
        *done = 1;
        return;
    }
    if (s->owner->header->id != s->id) {
        *done = 1;
        return;
    }
    s->rx += fixed_mul(s->vx, D_800DE30C);
    s->ry += fixed_mul(s->vy, D_800DE30C);
    s->rz += fixed_mul(s->vz, D_800DE30C);
}
