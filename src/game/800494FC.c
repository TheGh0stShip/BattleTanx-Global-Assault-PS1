typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

int func_800494FC(VecXZ *a, VecXZ *b, VecXZ *c) {
    s32 az;
    s32 bz;
    s32 bx;
    s32 cx;
    s32 ax;
    s32 cz;
    register s32 first asm("$3");
    register s32 second asm("$2");
    register s32 side asm("$8");

    az = a->z;
    bz = b->z;
    bx = b->x;
    cx = c->x;
    first = az - bz;
    second = cx - bx;
    asm volatile("" : "+r"(first), "+r"(second));
    side = (first >> 16) * (second >> 16);
    ax = a->x;
    cz = c->z;
    first = ax - bx;
    second = cz - bz;
    asm volatile("" : "+r"(side));
    first >>= 16;
    second >>= 16;
    asm volatile("" : "+r"(first), "+r"(second));
    asm volatile(
        ".set noreorder\n\t"
        "mult $2,$3\n\t"
        "mflo $3\n\t"
        "subu $2,$8,$3");
    asm volatile("" : "+r"(second));

    if (second > 0) {
        return 1;
    }
    return (second >> 31) & 2;
}
