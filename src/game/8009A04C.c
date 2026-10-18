extern int func_80094420(int kind, int value);

int func_8009A04C(int value)
{
    volatile char outgoing[16];
    register int argument asm("$5");
    register int result asm("$2");

    asm volatile("" : : : "$31", "memory");
    asm("addu %0,%1,$zero" : "=r"(argument) : "r"(value));
    asm volatile(
        ".set noreorder\n\t"
        "jal func_80094420\n\t"
        "addiu $4,$zero,8\n\t"
        ".set reorder"
        : "=r"(result)
        : "r"(argument)
        : "$4", "$31", "memory"
    );
    return result;
}
