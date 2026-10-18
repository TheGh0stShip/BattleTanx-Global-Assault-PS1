extern void func_8009AA74(int value);

void func_800A2F90(void)
{
    volatile char outgoing[16];

    asm volatile(
        ".set noreorder\n\t"
        "jal func_8009AA74\n\t"
        "addu $4,$zero,$zero\n\t"
        ".set reorder"
        :
        :
        : "$4", "$31", "memory"
    );
}
