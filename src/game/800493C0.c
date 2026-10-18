typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SmallState {
    u32 value;
    u16 index;
    u8 mode;
} SmallState;

void func_800493C0(SmallState *source, SmallState *state) {
    state->value = source->value;
    state->index = source->index;
    state->mode = source->mode;
}
