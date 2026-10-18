typedef unsigned char u8;

typedef struct VehicleState {
    u8 pad_000[0x188];
    int deadline;
    u8 pad_18C[0x218 - 0x18C];
    unsigned int flags;
} VehicleState;

extern int D_800D2FE0;
extern void func_8004E0BC(VehicleState *state);
extern void func_8004D7D8(VehicleState *state);

void func_8004FAF4(VehicleState *state) {
    state->flags &= ~0x100;
    state->deadline = D_800D2FE0 + 120;
    func_8004E0BC(state);
    func_8004D7D8(state);
}
