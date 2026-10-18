typedef signed short s16;

extern void func_80093590(int type, int value);
extern int func_80091A90(int first, int second);
extern int func_8009383C(void *entry, int arg1, int arg2, int variant,
                        int arg4, void (*callback)(void *));
extern void func_8006AEE8(void *context);
extern void *D_800ADE3C[];
extern s16 D_800E540C;

void func_8006AF1C(int index, int variant) {
    int saved_index = index;
    register int saved_variant asm("$17");
    register int zero asm("$5");
    register int third asm("$6");

    func_80093590(4, saved_variant = variant);
    func_80091A90(D_800E540C, D_800E540C);
    zero = 0;
    third = zero;
    func_8009383C(D_800ADE3C[saved_index], zero, third,
                  saved_variant & 0xFF, 0, func_8006AEE8);
}
