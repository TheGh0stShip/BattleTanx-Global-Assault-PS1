typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RefreshState {
    u8 pad_00[8];
    u16 previous;
    u16 current;
    u32 query;
    u32 update_previous;
} RefreshState;

extern u16 func_8004D8E0(void *object, u32 *query);

void func_80048F2C(void *object, RefreshState *state) {
    u16 value = func_8004D8E0(object, &state->query);

    state->current = value;
    if (state->update_previous != 0) {
        state->previous = value;
    }
}
