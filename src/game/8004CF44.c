typedef unsigned short u16;

int func_8004C278(unsigned char *object);
void func_8004D178(unsigned char *object);

void func_8004CF44(unsigned char *object) {
    u16 *state = (u16 *)(object + 0x13C);

    if (*(int *)(object + 0x114) == 2) {
        state[6] = 0;
        return;
    }
    if ((*(unsigned int *)(object + 0x180) & 1) != 0) {
        if (func_8004C278(object) == 0) {
            state[6] = 0;
        }
        return;
    }
    if (state[6] != 0) {
        func_8004D178(object);
    }
}
