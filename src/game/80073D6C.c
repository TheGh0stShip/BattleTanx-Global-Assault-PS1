typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct SVec {
    short x;
    short y;
    short z;
    short pad;
} SVec;

typedef struct Part {
    int pad0[2];
    struct Part *next;
    SVec offset;
    Vec pos;
    Vec vel;
    unsigned short rx;
    unsigned short ry;
    unsigned short rz;
    short spin_x;
    short spin_y;
    short spin_z;
} Part;

typedef struct Debris {
    int pad0[7];
    Part *parts;
    int timer;
} Debris;

extern int D_800DE30C;
extern void func_8002382C(Part *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80073D6C(Debris *arg0, int *done) {
    Debris *debris = arg0;
    Part *part = debris->parts;
    Part *piece;
    int dt;

    if (part == 0) {
        *done = 1;
        return;
    }
    debris->timer -= D_800DE30C;
    if (debris->timer <= 0) {
        for (piece = debris->parts; piece != 0; piece = piece->next) {
            func_8002382C(piece);
        }
        debris->parts = 0;
        *done = 1;
        return;
    }
    dt = D_800DE30C;
    do {
        part->pos.x += fixed_mul(dt, part->vel.x);
        part->pos.y += fixed_mul(dt, part->vel.y);
        part->pos.z += fixed_mul(dt, part->vel.z);
        part->rx += fixed_mul(dt, part->spin_x);
        part->ry += fixed_mul(dt, part->spin_y);
        part->rz += fixed_mul(dt, part->spin_z);
        if (part->pos.y < 0) {
            part->pos.y = 0;
            part->vel.x /= 2;
            part->vel.z /= 2;
            part->vel.y = -part->vel.y / 4;
            part->spin_x = -part->spin_x / 2;
            part->spin_y = -part->spin_y / 2;
            part->spin_z = -part->spin_z / 2;
        }
        if (part->pos.y > 0) {
            part->vel.y -= fixed_mul(dt, 6144);
        }
        part = part->next;
    } while (part != 0);
}
