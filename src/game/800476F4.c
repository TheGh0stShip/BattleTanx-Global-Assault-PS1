typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object {
    u8 pad_000[0x9C];
    u32 table_index;
    u8 pad_0A0[0x218 - 0xA0];
    u32 flags;
} Object;

typedef struct Entry {
    u8 pad_00[0x5C];
    int state_fixed;
    u8 pad_60[0xD0 - 0x60];
} Entry;

extern Entry D_800A4EF4[];
extern u8 D_800AED53;

int func_800476F4(Object *object, int message) {
    int state;

    switch (message) {
    case 1:
        state = D_800A4EF4[object->table_index].state_fixed >> 12;
        if ((object->flags & 2) && (D_800AED53 & 1) && state >= 6) {
            state = 5;
        }
        return state;
    case 12:
        return 5;
    default:
        return 30;
    }
}
