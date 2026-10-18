typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern int func_8004920C(s32 x, s32 z);

int func_80049814(VecXZ *vector) {
    return func_8004920C(vector->x, vector->z);
}
