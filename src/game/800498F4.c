typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectSlot {
    u8 pad_000[0xA8];
    u32 mask;
    u8 pad_0AC[0x4EC];
} ObjectSlot;

typedef struct ObjectPair {
    u8 first;
    u8 second;
} ObjectPair;

extern ObjectSlot D_800DE33C[];
extern u16 D_800E3CBC;
extern u32 D_800E3CC0;
extern ObjectPair D_800E3CC4[];

typedef char ObjectSlot_size[(sizeof(ObjectSlot) == 0x598) ? 1 : -1];

void func_800498F4(void) {
    u16 index;
    u32 mask;
    u8 first;
    u8 second;

    index = 0;
    mask = 1;
    for (; index < 16; index++) {
        D_800DE33C[index].mask = mask;
        mask <<= 1;
    }

    index = 0;
    for (first = 0; first < 16; first++) {
        for (second = first + 1; second < 16; second++) {
            D_800E3CC4[index].first = first;
            D_800E3CC4[index].second = second;
            index++;
        }
    }

    D_800E3CBC = 0x77;
    D_800E3CC0 = 0;
}
