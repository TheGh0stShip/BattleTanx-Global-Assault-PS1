typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern int func_8004920C(s32 x, s32 z);

int func_800495D8(VecXZ *left, VecXZ *right) {
    return func_8004920C(left->x - right->x, left->z - right->z);
}
