typedef unsigned char u8;
typedef signed short s16;

typedef struct InnerState {
    u8 pad_00[0xA0];
    int state;
} InnerState;

typedef struct Entry {
    u8 pad_00[4];
    s16 type;
    u8 pad_06[2];
    InnerState *inner;
} Entry;

typedef struct Result {
    int kind;
    int pad_04;
    void *value;
} Result;

void func_8003748C(void *base, Entry *entry, int blocked, int unused,
                   Result *result) {
    if (blocked != 0) {
        return;
    }
    if (entry->type != 4) {
        result->kind = 2;
        return;
    }

    {
        int state = entry->inner->state;

        if (state == 1) {
            goto set_two;
        }
        if (state == 0) {
            goto special;
        }
        if (state != 2) {
            goto set_two;
        }
    }

special:
    result->kind = 7;
    result->value = (u8 *)base + 8;
    return;

set_two:
    result->kind = 2;
}
