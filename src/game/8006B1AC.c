typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Item {
    char pad_00[6];
    u8 kind;
    char pad_07;
    s16 value;
    char pad_0A[2];
    void *first;
    void *second;
    u8 extra;
    char pad_15[7];
    u32 state;
} Item;

extern Item *func_8002380C(int pool, int size);

Item *func_8006B1AC(
    void *first,
    void *second,
    s16 value,
    u32 kind,
    u8 extra
) {
    Item *item = func_8002380C(3, 0x20);

    if (item == 0) {
        return 0;
    }

    item->kind = kind;
    if (kind < 3) {
        item->value = value;
        item->first = first;
        item->second = second;
        item->extra = extra;
        item->state = 0;
    }

    return item;
}
