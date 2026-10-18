extern char *func_80088870(int value);

void func_80081B28(void)
{
    volatile char outgoing[16];
    register char *result asm("$2");

    asm volatile(
        ".set noreorder\n\t"
        "jal func_80088870\n\t"
        "addiu $4,$zero,-1\n\t"
        ".set reorder"
        : "=r"(result)
        :
        : "$4", "$31", "memory"
    );
    *(char **)0x800B0D6C = result + 0xF0;
    *(int *)0x800B0D70 = 0;
    asm volatile("" : : : "$31", "memory");
}
