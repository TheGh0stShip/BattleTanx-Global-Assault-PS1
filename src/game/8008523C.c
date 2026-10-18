typedef unsigned char u8;

typedef struct Entry {
    u8 first;
    u8 second;
    u8 padding[2];
} Entry;

typedef struct Table {
    u8 padding[12];
    Entry entries[1];
} Table;

extern Table D_800EDF78;

void func_8008523C(int index, u8 second, u8 first) {
    D_800EDF78.entries[index].first = first;
    D_800EDF78.entries[index].second = second;
}
