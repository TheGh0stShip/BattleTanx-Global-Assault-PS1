typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

void func_8004960C(VecXZ *result, VecXZ *left, VecXZ *right) {
    result->x = right->x - left->x;
    result->z = right->z - left->z;
}
