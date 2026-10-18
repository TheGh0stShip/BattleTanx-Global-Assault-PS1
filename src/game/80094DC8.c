typedef struct RuntimeState {
    int first;
    int second;
    int third;
    int pad_0C;
    int current;
} RuntimeState;

extern void func_8009F59C(void);
extern void func_80096840(void);
extern int func_800944B4(int kind, void (*callback)(void));
extern void func_80096690(void);

void func_80094DC8(void)
{
    volatile char outgoing[16];
    register RuntimeState *state asm("$2");
    register int invalid asm("$3");
    register void (*callback)(void) asm("$5");

    asm volatile(
        ".set noreorder\n\t"
        "jal func_8009F59C\n\t"
        "nop\n\t"
        ".set reorder"
        :
        :
        : "$31", "memory"
    );
    asm(
        "lui %0,0x800F\n\t"
        "addiu %0,%0,-0x0F6C"
        : "=r"(state)
    );
    invalid = -1;
    state->first = 0;
    state->second = 0;
    state->third = 0;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_80096840\n\t"
        "sw $3,16($2)\n\t"
        ".set reorder"
        :
        : "r"(state), "r"(invalid)
        : "$31", "memory"
    );
    callback = func_80096690;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_800944B4\n\t"
        "addiu $4,$zero,7\n\t"
        ".set reorder"
        :
        : "r"(callback)
        : "$4", "$31", "memory"
    );
}
