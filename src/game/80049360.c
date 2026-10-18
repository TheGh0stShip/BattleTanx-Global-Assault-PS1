typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SmallState {
    u32 value;
    u16 index;
    u8 mode;
} SmallState;

void func_80049360(SmallState *state) {
    state->value = 0;
    state->index = 0xFFFF;
    state->mode = 0;
}
