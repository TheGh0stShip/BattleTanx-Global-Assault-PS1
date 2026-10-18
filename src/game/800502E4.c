extern void func_8004E0BC(void);
extern void func_8004D804(void *object);

void func_800502E4(unsigned char *object) {
    int *state = (int *)(object + 0x184);
    state[0] = 1;
    *(int *)(object + 0x218) &= ~0x100;
    state[1] = 0;
    state[2] = 0;
    state[3] = 0;
    func_8004E0BC();
    func_8004D804(object);
}
