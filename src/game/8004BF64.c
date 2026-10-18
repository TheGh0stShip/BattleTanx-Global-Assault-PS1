struct ResetBlock {
    unsigned int field_00;
    unsigned char pad_04[2];
    unsigned short field_06;
    unsigned char pad_08[2];
    unsigned short field_0A;
    unsigned char pad_0C[8];
    unsigned short field_14;
    unsigned short field_16;
    unsigned int field_18;
};

struct ResetState {
    unsigned char pad_000[0xF8];
    struct ResetBlock block;
    unsigned char pad_114[0x36];
    unsigned short field_14A;
    unsigned char pad_14C[0x34];
    unsigned int flags_180;
};

void func_8004A160(void *value, int mode);

void func_8004BF64(struct ResetState *state) {
    register struct ResetBlock *block asm("$16") = &state->block;

    state->field_14A = 0;
    func_8004A160((unsigned char *)state + 0xFC, 0);
    block->field_06 = 0;
    block->field_00 = 0;
    block->field_0A = 0;
    block->field_14 = 0;
    block->field_16 = 0;
    block->field_18 = 0;
    state->flags_180 &= ~0x180;
}
