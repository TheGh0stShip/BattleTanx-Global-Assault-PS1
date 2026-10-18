typedef signed int s32;

extern char D_800EC288[];
extern void func_8007E974(void *state, void *argument);
extern s32 func_80094294(void *state, s32 index);

s32 func_8007EAC8(void *argument) {
    s32 result;

    func_8007E974(D_800EC288, argument);
    result = func_80094294(D_800EC288, 0);
    if (result == -1)
        result = 0;
    else
        result++;
    return result;
}
