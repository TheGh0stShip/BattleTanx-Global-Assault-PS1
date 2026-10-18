typedef struct State {
    unsigned int unused0;
    volatile unsigned int flags;
    unsigned int padding[7];
    unsigned int value_24;
    unsigned int value_28;
    unsigned int active;
} State;

extern State D_800EEDF4;
extern void func_8008F4B4(int value);
extern void func_8008F368(int value);

void func_8008FA34(void) {
    int enabled = 1;

    if (D_800EEDF4.active != 0) {
        D_800EEDF4.flags |= 4;
        enabled = 0;
        func_8008F4B4(enabled);
        enabled = 1;
    }
    D_800EEDF4.value_24 = 0;
    D_800EEDF4.value_28 = 0;
    D_800EEDF4.flags &= -80;
    func_8008F368(enabled);
}
