typedef struct { int x, y, z; } Vector;
typedef struct { short x, y, z; } SVector;
int func_8008AD60(int);
int func_8008ACC0(int);
void func_800738D4(int, Vector *, int, SVector *, int);
void func_8003BADC(int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_80035878(int model, Vector *pos, unsigned short angle, unsigned short tilt) {
    SVector up;

    up.x = func_8008AD60(tilt >> 4) << 2;
    up.z = func_8008ACC0(tilt >> 4) << 2;
    up.y = 1024;
    if (model != 0) {
        func_800738D4(model, pos, angle, &up, 100);
        func_8003BADC(to_int(pos->x), to_int(pos->z));
    }
}
