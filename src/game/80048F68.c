typedef unsigned char u8;
typedef signed int s32;

typedef struct SnapshotState {
    u8 pad_000[8];
    s32 x;
    u8 pad_00C[4];
    s32 z;
    u8 pad_014[0x15C];
    s32 snapshot_x;
    u8 pad_174[4];
    s32 snapshot_z;
} SnapshotState;

void func_80048F68(SnapshotState *state) {
    state->snapshot_x = state->x;
    state->snapshot_z = state->z;
}
