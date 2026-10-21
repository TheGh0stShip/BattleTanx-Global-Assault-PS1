typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

extern s16 *D_800B76F0;
extern s32 D_800B7714;
extern s32 D_800B7718;
extern u32 D_800B771C;
extern volatile s32 D_800B7720;

u32 func_8009A8C0(s32 index, u32 value) {
    register s32 saved_index asm("$6") = index;
    register u32 shifted asm("$7");
    register u32 result asm("$2");

    if (D_800B7714 != 0) {
        register u32 divisor asm("$4");
        register u32 remainder asm("$2");
        __asm__ volatile (
            "lui %0,%%hi(D_800B771C)\n\t"
            "lw %0,%%lo(D_800B771C)(%0)"
            : "=r"(divisor));
        __asm__ volatile (
            ".set noreorder\n\t"
            "divu $0,%1,%2\n\t"
            "bnez %2,1f\n\t"
            "nop\n\t"
            "break 7\n"
            "1:\n\t"
            "mfhi %0\n\t"
            ".set reorder"
            : "=r"(remainder)
            : "r"(value), "r"(divisor));
        if (remainder != 0) {
            register s32 align_mask asm("$2");
            __asm__ volatile ("" : "+r"(remainder));
            align_mask = D_800B7720;
            value += divisor;
            align_mask = ~align_mask;
            value &= align_mask;
        }
    }
    {
        register s32 shift asm("$2") = D_800B7718;
        __asm__ volatile ("" : "+r"(shift));
        shifted = value >> shift;
    }
    __asm__ volatile (
        ".set noreorder\n\t"
        "addiu $2,$0,-2\n\t"
        "beq $6,$2,2f\n\t"
        "addu $3,$7,$0\n\t"
        "addiu $2,$0,-1\n\t"
        "bne $6,$2,1f\n\t"
        "addu $2,$5,$0\n\t"
        "j 3f\n\t"
        "andi $2,$3,0xffff\n"
        "2:\n\t"
        "j 3f\n\t"
        "addu $2,$5,$0\n"
        "1:\n\t"
        "lui $4,%%hi(D_800B76F0)\n\t"
        "lw $4,%%lo(D_800B76F0)($4)\n\t"
        "sll $3,$6,1\n\t"
        "addu $3,$3,$4\n\t"
        "sh $7,0($3)\n"
        "3:\n\t"
        ".set reorder"
        : "=r"(result)
        : "r"(saved_index), "r"(value), "r"(shifted)
        : "$3", "$4", "memory");
    return result;
}
