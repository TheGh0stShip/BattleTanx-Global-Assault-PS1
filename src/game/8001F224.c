typedef struct Body {
    int vx;
    int vy;
    int vz;
    char pad0C[0x18 - 0xC];
    unsigned short kind;
} Body;
typedef struct Pos2 {
    int x;
    int y;
} Pos2;
void func_8001B4B8(void *, void *, int, Pos2 *, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8001F224(void *obj, Body *body, int scale, void *target, int flags) {
    Pos2 p;
    int amount = fixed_mul(scale, body->vz) * body->kind;

    p.x = body->vx;
    p.y = body->vy;
    func_8001B4B8(obj, target, amount, &p, flags);
}
