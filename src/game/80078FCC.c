typedef signed int s32;

typedef struct Owner {
    char pad_00[4];
    char *data;
} Owner;

extern s32 D_800AEB30;
extern char D_800AD9C8[];
extern char D_800AEA5C[];
extern char D_800E534C[];
extern s32 D_800EBC3C;
extern s32 D_800EBC40;
extern void func_80059550(void *state, Owner *owner, s32 enabled);
extern void func_8005A2F0(void *argument, char *data);
extern void func_80076E28(void *state);
extern void func_8008DA04(void *destination, void *source);

s32 func_80078FCC(Owner *owner, char *argument) {
    char *state = D_800AEA5C;

    D_800EBC40 = 0;
    D_800AEB30 = 4;
    D_800EBC3C = 0;
    func_80076E28(state);
    func_8008DA04(state + 0x58, D_800E534C);
    func_8005A2F0(argument, owner->data + 0x20);
    argument[1] = 0x10;
    func_80059550(D_800AD9C8, owner, 1);
    return 0;
}
