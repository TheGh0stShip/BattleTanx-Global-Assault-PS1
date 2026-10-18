typedef signed int s32;

typedef struct VecXZ {
    s32 x;
    s32 pad;
    s32 z;
} VecXZ;

extern s32 func_8008ABF0(s32 value);
extern s32 func_8008AE30(s32 x, s32 z);

int func_80049790(VecXZ *vector) {
    register s32 x asm("$6");
    register s32 z asm("$2");
    register s32 first_square asm("$3");
    register s32 sum asm("$4");
    s32 angle;

    x = vector->x;
    z = vector->z;
    asm volatile("" : "+r"(x), "+r"(z));
    asm volatile(
        ".set noreorder\n\t"
        "addu $7,$6,$0\n\t"
        "mult $6,$7\n\t"
        "mflo $3\n\t"
        "mfhi $4\n\t"
        "srl $3,$3,12\n\t"
        "sll $4,$4,20\n\t"
        "or $3,$3,$4\n\t"
        "mult $2,$2\n\t"
        "mflo $4\n\t"
        "mfhi $6\n\t"
        "srl $4,$4,12\n\t"
        "sll $6,$6,20\n\t"
        "or $4,$4,$6");
    asm volatile("" : "+r"(first_square), "+r"(sum));
    sum = first_square + sum;

    if (func_8008ABF0(sum) > 0) {
        angle = func_8008AE30(vector->x, vector->z);
        asm volatile("" : "+r"(angle));
        return (angle & 0xFFF) << 4;
    }
    return 0;
}
