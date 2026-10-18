typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ResetState {
    u8 pad_00[0xA];
    u16 field_0A;
    u8 pad_0C[8];
    u16 field_14;
    u16 field_16;
    u32 field_18;
} ResetState;

void func_8004C168(ResetState *state) {
    state->field_0A = 0;
    state->field_14 = 0;
    state->field_16 = 0;
    state->field_18 = 0;
}
