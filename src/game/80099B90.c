typedef unsigned int u32;

typedef struct RangeState {
    u32 pad_00[2];
    u32 limit;
    u32 base;
    u32 pad_10[2];
    u32 quantum;
} RangeState;

u32 func_80099B90(RangeState *state, u32 offset) {
    register u32 adjusted asm("$5");
    register u32 limit asm("$6");
    register u32 quantum asm("$4");
    register u32 quotient asm("$2");
    register u32 value asm("$3");

    adjusted = state->base + offset;
    value = 0;
    limit = state->limit;
    if (!(limit < adjusted)) {
        goto done;
    }
    quantum = state->quantum;
    value = adjusted - limit;
    if (quantum != 0) {
        quotient = value + quantum;
        quotient--;
        asm volatile(
            ".set noreorder\n\t"
            "divu $0,$2,$4\n\t"
            "bnez $4,1f\n\t"
            "nop\n\t"
            "break 0x1C00\n"
            "1:\n\t"
            "mflo $2\n\t"
            "nop\n\t"
            "nop\n\t"
            "mult $2,$4\n\t"
            "mflo $3");
        asm volatile("" : "+r"(value), "+r"(quotient));
    }
done:
    return value;
}
