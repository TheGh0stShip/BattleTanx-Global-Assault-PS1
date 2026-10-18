typedef signed int s32;

typedef struct Target {
    char pad_00[0x28];
    void *field_28;
} Target;

typedef struct State {
    char pad_00[4];
    Target *target;
} State;

extern s32 D_800AEB30;
extern State D_800A9A88;
extern char D_800AEA5C[];
extern char D_800EAC90[];
extern s32 D_800EBC3C;
extern s32 D_800EBC40;
extern void func_80059550(State *state, void *argument, s32 enabled);
extern void func_80076E28(void *state);

s32 func_80078E54(void *argument) {
    D_800EBC40 = 0;
    D_800AEB30 = 3;
    D_800EBC3C = 0;
    func_80076E28(D_800AEA5C);
    D_800A9A88.target->field_28 = D_800EAC90;
    func_80059550(&D_800A9A88, argument, 1);
    return 0;
}
