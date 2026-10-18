typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectRecord {
    u8 pad_00[0xA8];
    u16 alternate;
    u16 primary;
    u8 pad_AC[0x24];
} ObjectRecord;

typedef struct ObjectState {
    u8 pad_00[0x9C];
    u32 record_index;
    u8 pad_A0[0xE0];
    u32 flags;
} ObjectState;

typedef char ObjectRecord_size[(sizeof(ObjectRecord) == 0xD0) ? 1 : -1];
typedef char ObjectState_size[(sizeof(ObjectState) == 0x184) ? 1 : -1];

extern ObjectRecord D_800A4EF4[];

u16 func_80049560(ObjectState *object, int use_primary) {
    if (use_primary || (object->flags & 8)) {
        return D_800A4EF4[object->record_index].primary;
    }
    return D_800A4EF4[object->record_index].alternate;
}
