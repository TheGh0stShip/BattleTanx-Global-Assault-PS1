extern unsigned char D_80086058[];

void *func_80086A70(unsigned int size) {
    register void *volatile *global_pointer asm("$28");
    unsigned char *allocation;
    unsigned char *state;
    unsigned char *next;
    void *result = 0;

    size = (size + 3) & -4;
    state = D_80086058;
    allocation = *(unsigned char **)(state + 0x30);
    next = allocation + size;
    if (next <= *(unsigned char **)(state + 0x34)) {
        result = allocation;
        *(unsigned char **)(state + 0x30) = next;
        global_pointer[0x30 / 4] = result;
        global_pointer[0x34 / 4] = result;
    }
    return result;
}
