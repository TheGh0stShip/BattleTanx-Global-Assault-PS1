void func_8008532C(unsigned int *state, unsigned int *node, unsigned int size,
                   unsigned int bucket) {
    unsigned int *slot = state + bucket;
    unsigned int *current = (unsigned int *)slot[2];
    unsigned int *previous = 0;

    while (current != 0) {
        if (current == node) {
            current = (unsigned int *)current[3];
            if (previous == 0) {
                slot[2] = (unsigned int)current;
            } else {
                previous[3] = (unsigned int)current;
            }
            state[1] -= size;
            return;
        }
        previous = current;
        current = (unsigned int *)current[3];
    }
}
