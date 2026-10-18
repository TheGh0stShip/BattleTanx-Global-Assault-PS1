typedef struct State {
    unsigned int padding[3];
    unsigned int flags;
} State;

extern State D_800EEDF4;

unsigned int func_8008F988(void) {
    unsigned int previous = D_800EEDF4.flags;
    D_800EEDF4.flags = previous & 4;
    return previous;
}
