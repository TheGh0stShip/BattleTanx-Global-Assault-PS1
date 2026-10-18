typedef unsigned int u32;

extern u32 D_800B7724;
extern u32 D_800B7728;
extern void func_8009A7F8(void *state, u32 value);

static inline u32 clear_state_flag(u32 value) {
    register u32 result asm("$2");

    asm volatile(
        "lui %0,%%hi(D_800B7728)\n\t"
        "lw %0,%%lo(D_800B7728)(%0)\n\t"
        "nop\n\t"
        "bnez %0,1f\n\t"
        "move %0,%1\n\t"
        "lui $1,%%hi(D_800B7724)\n\t"
        "sw $0,%%lo(D_800B7724)($1)\n"
        "1:"
        : "=&r"(result)
        : "r"(value)
        : "$1", "memory");
    return result;
}

u32 func_80090344(void *state, u32 value) {
    if (value > 0x7EFF0)
        value = 0x7EFF0;
    func_8009A7F8(state, value);
    return clear_state_flag(value);
}
