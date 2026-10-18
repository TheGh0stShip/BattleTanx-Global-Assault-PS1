typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectSlot {
    u8 bytes[0x598];
} ObjectSlot;

extern ObjectSlot D_800DE33C[];

ObjectSlot *func_80049E70(u32 mask) {
    u16 index;

    if (mask == 0) {
        return 0;
    }
    index = 0;
    while ((mask & 1) == 0) {
        mask >>= 1;
        index++;
    }
    return &D_800DE33C[index];
}
