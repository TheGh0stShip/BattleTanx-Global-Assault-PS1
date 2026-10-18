typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SmallState {
    u32 value;
    u16 index;
    u8 mode;
} SmallState;

typedef struct StateSource {
    s16 *value;
    u16 index;
    u8 pad[26];
    u8 mode;
} StateSource;

void func_80049384(SmallState *state, StateSource *source) {
    if (source->value == 0) {
        state->value = 0;
    } else {
        state->value = *source->value;
    }
    state->index = source->index;
    state->mode = source->mode;
}
