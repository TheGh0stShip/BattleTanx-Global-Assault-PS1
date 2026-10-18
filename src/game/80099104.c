typedef signed int s32;

typedef struct State {
    s32 fields[20];
} State;

extern unsigned char D_800991E8[];
extern s32 func_800A2C10(State *state, s32 mode, s32 zero_a, s32 zero_b,
                         void *table);
extern void func_80098D50(State *state, s32 zero_a, s32 zero_b);

void func_80099104(State *state, s32 unused_a, s32 unused_b, s32 enabled) {
    if (enabled != 0) {
        state->fields[19] = 3;
        if (func_800A2C10(state, 5, 0, 0, D_800991E8) != 0) {
            return;
        }
    }
    asm volatile("");
    func_80098D50(state, 0, 0);
}
