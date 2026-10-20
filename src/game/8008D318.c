typedef struct PoolNode {
    struct PoolNode *next;
    struct PoolNode *previous;
    unsigned char payload[8];
} PoolNode;

typedef struct PoolState {
    PoolNode *first;
    int active;
    unsigned char control[0x80];
} PoolState;

extern void func_8008AA48(void *destination, int value, unsigned int size);
extern void func_8008D2CC(PoolState *state, int mode, int first, int second, int third);

void func_8008D318(PoolState *state, PoolNode *nodes, int count, int mode,
                   int first, int second, int third) {
    register PoolState *saved_state asm("$18") = state;
    register PoolNode *node asm("$17") = nodes;
    register int remaining asm("$16") = count;
    register int saved_mode asm("$19") = mode;
    register PoolNode *previous asm("$3");
    register PoolNode *next asm("$2");

    asm("" : "+r"(saved_state), "+r"(node), "+r"(remaining), "+r"(saved_mode));
    saved_state->first = node;
    saved_state->active = 0;
    func_8008AA48(saved_state->control, 0, 0x80);
    previous = 0;
    if (remaining != 0) {
        do {
            node->previous = previous;
            previous = node;
            next = previous + 1;
            asm("" : "+r"(next));
            previous->next = next;
            asm volatile("" : : "m"(previous->next) : "memory");
            remaining--;
            node = next;
        } while (remaining != 0);
    }
    previous->next = 0;
    func_8008D2CC(saved_state, saved_mode, first, second, third);
}
