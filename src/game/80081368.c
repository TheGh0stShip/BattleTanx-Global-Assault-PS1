extern int func_8008138C(int first, int second, int third, int fourth);

int func_80081368(int first, int second, int third)
{
    volatile char outgoing[16];
    register int fourth asm("$7");
    register int result asm("$2");

    asm volatile("" : : : "$31", "memory");
    asm("addu %0,%1,$zero" : "=r"(fourth) : "r"(third));
    asm volatile(
        ".set noreorder\n\t"
        "jal func_8008138C\n\t"
        "addu $6,$zero,$zero\n\t"
        ".set reorder"
        : "=r"(result)
        : "r"(first), "r"(second), "r"(fourth)
        : "$6", "$31", "memory"
    );
    return result;
}
