typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SmallState {
    u32 value;
    u16 index;
} SmallState;

int func_80049438(SmallState *left, SmallState *right) {
    int equal = 0;

    if (left->value == right->value) {
        equal = left->index == right->index;
    }
    return equal;
}
