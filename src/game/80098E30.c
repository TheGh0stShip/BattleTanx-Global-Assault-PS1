struct ActionState {
    unsigned char pad_00[0x4C];
    int action;
};

extern unsigned char D_800991E8[];

int func_800A2B78(struct ActionState *state, int selected, unsigned char *data);
void func_80098D50(struct ActionState *state, int mode, int result);

void func_80098E30(
    struct ActionState *state,
    unsigned int selection,
    int unused,
    int enabled
) {
    int result = enabled;

    if (result != 0) {
        state->action = 9;
        result = func_800A2B78(state, (unsigned char)selection == 5, D_800991E8);
        if (result != 0) {
            return;
        }
    }
    func_80098D50(state, 1, result);
}
