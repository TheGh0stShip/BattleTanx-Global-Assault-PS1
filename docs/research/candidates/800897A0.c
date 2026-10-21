typedef struct StreamState {
    unsigned char unused0[0x3A];
    unsigned char busy;
    unsigned char deferred;
    unsigned char unused3C[0x54];
    unsigned int length;
    unsigned char unused94[4];
    int handle;
    unsigned char transfer[1];
} StreamState;

extern StreamState D_800EEAE8;
extern void func_80089518(void);
extern unsigned int func_80088B24(unsigned int length);
extern void func_80088E48(int event);
extern int func_80089098(int value);
extern void func_80089A58(void);
extern void func_80091618(void (*callback)(void));
extern int func_80097518(int handle, int size);
extern unsigned int func_800976A0(void *transfer);

void func_800897A0(void) {
    StreamState *state;
    unsigned int length;

    func_80091618(0);
    state = &D_800EEAE8;
    if (state->busy != 0) {
        state->deferred = 1;
        return;
    }
    if (func_800976A0(state->transfer) != (state->length >> 11)) {
        func_80089A58();
        return;
    }
    length = state->length;
    state->handle = func_80088B24(length);
    func_80091618(func_80089518);
    if (func_80097518(state->handle, 0x200) != 0) {
        return;
    }
    if (func_80089098(1) != 0) {
        func_80089A58();
        return;
    }
    func_80088E48(5);
}
