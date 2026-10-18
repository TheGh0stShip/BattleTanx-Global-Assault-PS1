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
extern char D_800EAC30[];
extern s32 D_800EBC3C;
extern void func_80059550(State *state, void *argument, s32 enabled);

s32 func_80078DAC(void *argument) {
    D_800EBC3C = 0;
    D_800AEB30 = 1;
    D_800A9A88.target->field_28 = D_800EAC30;
    func_80059550(&D_800A9A88, argument, 1);
    return 0;
}
