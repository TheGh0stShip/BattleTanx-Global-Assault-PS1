typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectDefinition {
    u8 pad_00[0x10];
    u32 flags;
    u8 pad_14[0xBC];
} ObjectDefinition;

typedef struct ObjectState {
    u8 pad_000[0x2C];
    u16 angle;
    u8 pad_02E[0x6E];
    u32 definition_index;
} ObjectState;

typedef struct QueryState {
    u8 pad_00[0xA];
    u16 angle;
    u32 enabled;
} QueryState;

extern ObjectDefinition D_800A4EF4[];
extern u16 D_800DE30C;
extern u16 func_80047AC8(void *value, u16 angle, u16 mask);
extern u16 func_80047B8C(u16 left, u16 right);
extern u16 func_80047B98(u16 left, u16 right);

typedef char ObjectDefinition_size[(sizeof(ObjectDefinition) == 0xD0) ? 1 : -1];

int func_80048FB0(ObjectState *object, QueryState *query) {
    u16 value;
    int result;

    if (D_800A4EF4[object->definition_index].flags & 1) {
        value = func_80047B8C(object->angle, query->angle);
        value = func_80047AC8((u8 *)object + 0x30, value,
                              (D_800DE30C << 10) & 0xFC00);
        if (value <= 0x400) {
            value = 0;
        } else {
            value -= 0x400;
        }
    } else {
        value = func_80047B98(object->angle, query->angle);
    }

    result = 0;
    if (query->enabled != 0) {
        result = value < 0x16D;
    }
    return result;
}
