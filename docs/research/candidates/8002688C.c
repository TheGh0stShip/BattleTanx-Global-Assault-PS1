typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct TableEntry {
    u32 flags;
    u32 value;
    u8 unused08[0x18];
    u16 type;
    u8 unused22[6];
} TableEntry;

typedef struct LinkedObject {
    u8 unused00[8];
    u8 *source;
    u8 unused0C[0x30];
    u32 link;
} LinkedObject;

typedef struct ObjectState {
    u8 unused00[6];
    u16 index;
    u8 unused08[0xF];
    u8 state;
    u8 unused18[0x10];
    LinkedObject *source;
    u8 unused2C[8];
    LinkedObject *destination;
    u8 unused38[2];
    short marker;
} ObjectState;

extern TableEntry D_800C62B0[];

void func_8002688C(ObjectState *object) {
    register ObjectState *saved asm("$6") = object;
    register TableEntry *base asm("$5");
    register TableEntry *entry asm("$2");
    register LinkedObject *destination asm("$4");
    register LinkedObject *source asm("$3");
    register LinkedObject *final_source asm("$4");
    register unsigned int index asm("$3");
    register unsigned int offset asm("$2");
    register unsigned int flags asm("$3");
    register unsigned int mask asm("$4");

    asm("" : "+r"(saved));
    if (saved->marker != -1) {
        saved->state = 7;
        asm("lui %0,%%hi(D_800C62B0)" : "=r"(base));
        destination = saved->destination;
        source = saved->source;
        asm("addiu %0,%0,%%lo(D_800C62B0)" : "+r"(base));
        destination->link = (u32)source;
        index = saved->index;
        asm("" : "+r"(index));
        offset = (index * 5) << 3;
        entry = (TableEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        flags = entry->flags;
        mask = 0x02000040;
        flags |= mask;
    } else {
        destination = saved->destination;
        source = saved->source;
        asm("lui %0,%%hi(D_800C62B0)" : "=r"(base));
        saved->state = 7;
        destination->link = (u32)source;
        index = saved->index;
        asm("" : "+r"(index));
        asm("addiu %0,%0,%%lo(D_800C62B0)" : "+r"(base));
        offset = (index * 5) << 3;
        entry = (TableEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        entry->value = 0;
        index = saved->index;
        asm("" : "+r"(index));
        offset = (index * 5) << 3;
        entry = (TableEntry *)offset;
        asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
        flags = entry->flags;
        flags |= 0x40;
    }
    entry->flags = flags;
    index = saved->index;
    asm("" : "+r"(index));
    offset = (index * 5) << 3;
    entry = (TableEntry *)offset;
    asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
    flags = entry->flags;
    mask = -3;
    flags &= mask;
    entry->flags = flags;
    index = saved->index;
    asm("" : "+r"(index));
    final_source = saved->source;
    asm("" : "+r"(final_source));
    offset = (index * 5) << 3;
    flags = *(u16 *)(final_source->source + 14);
    entry = (TableEntry *)offset;
    asm("addu %0,%0,%1" : "+r"(entry) : "r"(base));
    entry->type = (u16)flags;
}
