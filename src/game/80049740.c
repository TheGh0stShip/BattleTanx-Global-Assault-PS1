typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern int func_8004920C(s32 x, s32 z);
extern int func_8008AE30(s32 x, s32 z);

int func_80049740(VecXZ *vector) {
    if (func_8004920C(vector->x, vector->z) > 0) {
        return (func_8008AE30(vector->x, vector->z) & 0xFFF) << 4;
    }
    return 0;
}
