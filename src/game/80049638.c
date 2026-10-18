typedef signed int s32;
typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

void func_80049638(VecXZ *vector, s32 scale) {
    register s32 value asm("$6");
    register s32 result asm("$3");

    value = vector->x;
    asm volatile("" : "+r"(value), "+r"(scale));
    asm volatile(
        ".set noreorder\n\t"
        "nop\n\t"
        "mult $5,$6\n\t"
        "mflo $3\n\t"
        "mfhi $2\n\t"
        "srl $3,$3,12\n\t"
        "sll $2,$2,20\n\t"
        "or $3,$3,$2");
    asm volatile("" : "+r"(result));

    value = vector->z;
    vector->x = result;
    asm volatile("" : "+r"(value), "+r"(scale));
    asm volatile(
        ".set noreorder\n\t"
        "mult $5,$6\n\t"
        "mflo $3\n\t"
        "mfhi $2\n\t"
        "srl $3,$3,12\n\t"
        "sll $2,$2,20\n\t"
        "or $3,$3,$2");
    asm volatile("" : "+r"(result));
    vector->z = result;
}
