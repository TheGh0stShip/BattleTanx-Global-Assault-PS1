extern unsigned char D_80086058[];

void *func_80086AB4(unsigned char *allocation, unsigned int size) {
    register void *volatile *global_pointer asm("$28");
    void *result = 0;

    if (allocation != 0 && allocation == global_pointer[0x34 / 4]) {
        unsigned char *state = D_80086058;
        unsigned char *next;

        size = (size + 3) & -4;
        next = allocation + size;
        if (next <= *(unsigned char **)(state + 0x34)) {
            *(unsigned char **)(state + 0x30) = next;
            result = allocation;
        }
    }
    return result;
}
