extern void func_800A30D4(void);

void func_8009CEDC(int first, int second)
{
    volatile char outgoing[16];
    register int saved_second asm("$5") = second;

    *(int *)0x800EF230 = first;
    asm volatile(
        ".set noreorder\n\t"
        "lui $1,0x800F\n\t"
        "jal func_800A30D4\n\t"
        "sw $5,-0x0DC0($1)\n\t"
        ".set reorder"
        :
        : "r"(saved_second)
        : "$1", "$31", "memory"
    );
}
