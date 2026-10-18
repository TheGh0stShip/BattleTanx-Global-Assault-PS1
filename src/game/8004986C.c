typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern int func_80049088(VecXZ *delta, s32 limit);

int func_8004986C(VecXZ *position, VecXZ *target, s32 limit) {
    VecXZ delta;
    register VecXZ *delta_ptr = &delta;

    delta_ptr->x = target->x - position->x;
    delta_ptr->z = target->z - position->z;
    if (func_80049088(delta_ptr, limit)) {
        position->x += delta_ptr->x;
        position->z += delta_ptr->z;
        return 1;
    }
    return 0;
}
