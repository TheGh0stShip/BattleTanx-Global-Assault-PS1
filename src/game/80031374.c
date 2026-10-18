typedef struct LinkNode {
    unsigned char unknown[12];
    struct LinkNode *next;
} LinkNode;

typedef struct LinkState {
    unsigned char unknown[44];
    LinkNode *head;
    unsigned char unknown_30[12];
    int status;
} LinkState;

unsigned int func_80031374(LinkState *state) {
    register unsigned int result asm("$2") = state->status;
    register LinkNode *next asm("$3");

    if ((int)result <= 0) {
        goto nonpositive_status;
    }
    result = (unsigned int)state->head;
    next = ((LinkNode *)result)->next;
    if (next != 0) {
        do {
            result = (unsigned int)next;
            next = ((LinkNode *)result)->next;
        } while (next != 0);
        return result;
    }
    goto final_return;

nonpositive_status:
    asm volatile("");
    result = (unsigned int)state->head;

final_return:
    asm volatile("");
    return result;
}
