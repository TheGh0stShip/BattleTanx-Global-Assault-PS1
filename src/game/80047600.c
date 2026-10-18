struct PendingObject {
    unsigned char pad_00[8];
    void *object;
};

void func_80044C38(void *object);

void func_80047600(struct PendingObject *state, int *complete) {
    if (state->object != 0) {
        func_80044C38(state->object);
        if (state->object != 0) {
            return;
        }
    }
    *complete = 1;
}
