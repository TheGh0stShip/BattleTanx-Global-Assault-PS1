typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

void func_80049840(VecXZ *left, VecXZ *right) {
    left->x += right->x;
    left->z += right->z;
}
