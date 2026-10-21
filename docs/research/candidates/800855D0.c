typedef struct StreamState {
    unsigned char unused0[48];
    int current;
    int end;
} StreamState;

extern StreamState D_80086058;
extern unsigned char D_800C6074;
extern int func_800854EC(void *buffer, int current, int end, int unused);

void *func_800855D0(void) {
    register int *global_pointer asm("$28");
    StreamState *state;

    asm("" : "=r"(global_pointer));
    if (*global_pointer == 0) {
        state = &D_80086058;
        if (func_800854EC(&D_800C6074, state->current, state->end, 0) != 0) {
            state->current = state->end;
        }
    }
    return &D_800C6074;
}
