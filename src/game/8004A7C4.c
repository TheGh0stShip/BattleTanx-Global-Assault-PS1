typedef unsigned char u8;
typedef unsigned short u16;

typedef struct PoolEntry {
    u8 active;
    u8 pad_01[3];
    struct PoolEntry *next;
    u16 value;
    u8 pad_0A[0x1C - 0xA];
} PoolEntry;

typedef struct RuntimePool {
    u8 pad_0000[8];
    PoolEntry entries[0x800];
    PoolEntry *head;
} RuntimePool;

extern RuntimePool *D_800A5B24;

void func_8004A7C4(unsigned int value) {
    PoolEntry *entry;
    u16 index = value;

    if (index == 0) {
        entry = 0;
    } else {
        entry = &D_800A5B24->entries[index];
    }
    entry->next = D_800A5B24->head;
    D_800A5B24->head = entry;
    entry->value = value;
    entry->active = 1;
}
