typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct EffectState {
    u16 id;
    u8 pad_02[6];
    u16 value;
    u8 pad_0A[2];
    u16 height;
    u8 pad_0E[2];
    s16 x;
    u8 pad_12[6];
    s16 z;
} EffectState;

typedef struct Object {
    s32 kind;
    u8 pad_004[0x14C - 4];
    EffectState effect;
} Object;

extern u16 func_800162F0(s32 kind, s16 x, s16 z, s32 zero,
                         s32 min_y, s32 max_y, s32 min_x, s32 height,
                         s32 zero_2, s32 zero_3, u16 value, u32 mask);

void func_8004D0A0(Object *object) {
    EffectState *effect = &object->effect;

    if (effect->id == 0xFFFF) {
        effect->id = func_800162F0(object->kind, effect->x, effect->z, 0,
                                   -150, 150, -100,
                                   (s16)(effect->height + 100),
                                   0, 0, effect->value, 0xF8000000);
    }
}
