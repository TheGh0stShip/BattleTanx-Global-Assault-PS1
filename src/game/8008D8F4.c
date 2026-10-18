typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry {
    u8 pad_00[8];
    u16 values[4];
} Entry;

extern void func_8007FC88(u16 *values, void *output);
extern void func_8007FA74(int value);

void func_8008D8F4(Entry *entry, void *output, int finish) {
    u16 values[4];
    values[0] = entry->values[0];
    values[1] = entry->values[1];
    values[2] = entry->values[2];
    values[3] = entry->values[3];
    func_8007FC88(values, output);
    if (finish != 0) {
        func_8007FA74(0);
    }
}
