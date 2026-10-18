typedef struct State {
    unsigned int padding;
    volatile unsigned int flags;
} State;

extern State D_800EEDF4;

int func_8008F9A4(void) {
    int result = 0;

    if ((D_800EEDF4.flags & 0xF) != 0) {
        result = (D_800EEDF4.flags >> 1) & 4;
        if ((D_800EEDF4.flags & 4) != 0) {
            result = 3;
        } else if ((D_800EEDF4.flags & 2) != 0) {
            result = 2;
        } else if ((D_800EEDF4.flags & 1) != 0) {
            result = 1;
        }
        D_800EEDF4.flags &= ~0xF;
    }
    return result;
}
