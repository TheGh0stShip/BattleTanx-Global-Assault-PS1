typedef unsigned char u8;

typedef struct Vector {
    int x;
    int y;
    int z;
    int pad;
} Vector;

typedef struct State {
    u8 pad_000[8];
    Vector position;
    u8 pad_018[0x13C - 0x18];
    Vector goal;
} State;

extern int func_800494FC(Vector *, Vector *, void *);
extern int func_800495D8(Vector *, void *);

int func_8004CFFC(State *state, void *point_arg) {
    register void *point asm("$18") = point_arg;
    int result = 0;

    /* Behavior reference; the production source supplies the exact build. */
    if (point == 0 ||
        func_800494FC(&state->position, &state->goal, point) != 1 ||
        func_800495D8(&state->position, point) <= 0x1E000)
        result = 1;
    return result;
}
