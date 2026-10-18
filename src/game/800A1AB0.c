typedef struct State {
    int unused_00;
    unsigned int flags;
    int pad_08[6];
    int active;
} State;

extern void func_8008FA34(void);
extern void func_8008FB94(void);

void func_800A1AB0(State *state) {
    state->active = 0;
    state->flags &= ~2;
    asm volatile("" : : : "memory");
    func_8008FA34();
    func_8008FB94();
    state->active = 0;
}
