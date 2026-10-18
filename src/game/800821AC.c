extern unsigned char D_800EDC9C;
extern void func_80081E94(int input, int *slot, void **value, int unused);

int func_800821AC(int input, void **previous_value)
{
    register int previous_slot asm("$17") = *(int *)&D_800EDC9C;
    register unsigned char *base asm("$18") = &D_800EDC9C;
    int slot;
    void *value;

    if (previous_value != 0) {
        *previous_value = *(void **)(base + 4);
    }

    func_80081E94(input, &slot, &value, 0);
    if (slot != -1) {
        *(int *)&D_800EDC9C = slot;
        *(void **)(base + 4) = value;
    }

    return previous_slot;
}
