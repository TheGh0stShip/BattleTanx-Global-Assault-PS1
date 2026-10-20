typedef signed int s32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct PoolEntry {
    s32 flags;
    s32 value;
    u8 unused08[0x18];
    s16 type;
    u8 unused22[6];
} PoolEntry;

typedef struct ChildState {
    u8 unused00[0x3C];
    s32 value;
} ChildState;

typedef struct ObjectState {
    u8 unused00[0x24];
    s32 value;
    u8 unused28[4];
    ChildState *child;
    u8 unused30[5];
    u8 state;
    u8 type;
    u8 mode;
    u16 entry;
} ObjectState;

typedef struct GlobalState {
    s32 unused00;
    s32 mode;
    u8 unused08[8];
    s32 count;
} GlobalState;

extern PoolEntry D_800C62B0[];
extern GlobalState D_800D2FE4;

void func_8002EA70(ObjectState *object) {
    register ObjectState *saved asm("$6") = object;
    register ChildState *child asm("$2");
    register s32 value asm("$3");
    register unsigned int index asm("$3");
    register unsigned int offset asm("$2");
    register PoolEntry *base asm("$5");
    register PoolEntry *entry asm("$2");
    register s32 flags asm("$3");
    register s32 mask asm("$4");

    asm("" : "+r"(saved));
    child = saved->child;
    value = saved->value;
    child->value = value;
    index = saved->entry;
    asm("" : "+r"(index));
    if (index != 0xFFFF) {
        offset = (index * 5) << 3;
        base = D_800C62B0;
        asm("" : "+r"(base), "+r"(offset));
        entry = (PoolEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        entry->value = 0;
        index = saved->entry;
        asm("" : "+r"(index));
        offset = (index * 5) << 3;
        entry = (PoolEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        flags = entry->flags;
        flags |= 0x40;
        entry->flags = flags;
        index = saved->entry;
        asm("" : "+r"(index));
        offset = (index * 5) << 3;
        entry = (PoolEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        flags = entry->flags;
        mask = -3;
        flags &= mask;
        entry->flags = flags;
        index = saved->entry;
        asm("" : "+r"(index));
        offset = (index * 5) << 3;
        value = saved->type;
        entry = (PoolEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        entry->type = (s16)value;
        if ((unsigned int)(saved->mode - 1) < 2U) {
            if (D_800D2FE4.mode == 12) {
                D_800D2FE4.count--;
            }
        }
        saved->state = 5;
    }
}
