typedef struct { int x, y, z; } Vector;
typedef struct { unsigned char b[8]; } Tint;
extern Tint D_800BE5CC;
void func_800738D4(int, Vector *, int, Tint *, int);
void func_8003BADC(int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_80035948(int model, Vector *pos, unsigned short angle) {
    Tint tint = D_800BE5CC;

    if (model != 0) {
        func_800738D4(model, pos, angle, &tint, 100);
        func_8003BADC(to_int(pos->x), to_int(pos->z));
    }
}
