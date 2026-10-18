typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SmallState {
    u32 value;
    u16 index;
    u8 mode;
} SmallState;

extern u8 D_800A5B28[];
extern u8 D_800A5B30[];

void func_800493E4(SmallState *source, int type, SmallState *state) {
    u8 *table;
    u8 mode;

    state->value = source->value;
    state->index = source->index;
    mode = source->mode;
    if (type == 2 || type == 18) {
        table = D_800A5B28;
    } else {
        table = D_800A5B30;
    }
    state->mode = table[mode];
}
