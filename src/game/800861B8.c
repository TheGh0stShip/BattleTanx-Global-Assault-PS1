void func_800861B8(unsigned int *start, unsigned int *end, unsigned int value)
{
    asm volatile(
        ".set noreorder\n\t"
        "sltu $8,%0,%1\n\t"
        "beq $zero,$8,2f\n\t"
        "addi %1,%1,-4\n"
        "1:\n\t"
        "sw %2,0(%0)\n\t"
        "sltu $8,%0,%1\n\t"
        "bne $zero,$8,1b\n\t"
        "addi %0,%0,4\n"
        "2:\n\t"
        ".set reorder"
        : "+r"(start), "+r"(end)
        : "r"(value)
        : "$8", "memory"
    );
}
