struct QueryState {
    unsigned char pad_00[8];
    unsigned char position[0x24];
    unsigned short fallback;
};

struct QueryResult {
    unsigned int values[4];
};

void *func_8004D948(struct QueryState *state);
void func_8004960C(struct QueryResult *result, unsigned char *position, void *query);
unsigned int func_80049740(struct QueryResult *result);

unsigned int func_8004D8E0(struct QueryState *state, int *found) {
    struct QueryResult result;
    void *query = func_8004D948(state);
    unsigned int value;

    if (query == 0) {
        value = state->fallback;
        *found = 0;
    } else {
        func_8004960C(&result, state->position, query);
        value = func_80049740(&result);
        *found = 1;
    }
    return value & 0xFFFF;
}
