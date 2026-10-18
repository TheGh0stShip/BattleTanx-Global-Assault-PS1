extern int D_800E53F4;
extern int D_800ADD14[];

void func_8006A0DC(void) {
    int size = 0x19000;
    int *state = D_800ADD14;
    int start = D_800E53F4;
    int end = start + size - 4;

    state[2] = size;
    state[7] = size;
    state[3] = 0;
    state[0] = start;
    state[1] = end;
    state[4] = end;
    state[5] = start;
}
