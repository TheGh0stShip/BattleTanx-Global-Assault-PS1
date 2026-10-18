typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SmallState {
    s32 value;
    u16 index;
    u8 mode;
} SmallState;

typedef struct Pair {
    s32 x;
    s32 z;
} Pair;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern void func_8001A9B4(u16 index, u8 mode, u16 angle, Pair *right,
                          Pair *left);

void func_80049468(SmallState *state, s32 angle, VecXZ *left,
                   VecXZ *right) {
    Pair left_pair;
    Pair right_pair;
    s32 angle_units;

    if (angle >= 0) {
        angle_units = angle >> 12;
    } else {
        angle_units = -((-angle) >> 12);
    }
    func_8001A9B4(state->index, state->mode, angle_units,
                  &right_pair, &left_pair);
    left->x = left_pair.x;
    left->z = left_pair.z;
    right->x = right_pair.x;
    right->z = right_pair.z;
}
