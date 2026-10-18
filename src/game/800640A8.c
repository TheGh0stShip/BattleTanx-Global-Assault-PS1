typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Owner {
    char pad_00[4];
    char *data;
} Owner;

typedef struct State {
    char pad_00[0x14];
    u16 field_14;
} State;

extern State D_800AB6F0;
extern u8 D_800ABA5A;
extern void func_80059550(State *state, Owner *owner, s32 enabled);
extern void func_8005A2F0(void *argument, char *data);

s32 func_800640A8(Owner *owner, void *argument) {
    func_8005A2F0(argument, owner->data + 0x20);
    D_800AB6F0.field_14 = D_800ABA5A;
    func_80059550(&D_800AB6F0, owner, 1);
    return 0;
}
