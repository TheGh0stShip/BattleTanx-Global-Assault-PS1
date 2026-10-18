typedef unsigned char u8;

typedef struct Entry {
    u8 pad_00[0x28];
    void *pointer;
    u8 pad_2C[8];
    u8 value;
} Entry;

void func_8009ED98(Entry *entry, void *pointer, int value) {
    entry->pointer = pointer;
    entry->value = value;
}
