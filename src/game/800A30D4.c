extern void func_800A2FB0(int value, int setting);

void func_800A30D4(void)
{
    volatile char outgoing[20];
    register int setting asm("$5");

    asm volatile("" : : : "memory");
    setting = *(int *)0x800EF240;
    asm volatile("sw $31,16($sp)" : : "r"(setting) : "memory");
    *(int *)0x800EF23C = 0;
    *(int *)0x800EF238 = 0;
    *(int *)0x800EF234 = 0;
    *(int *)0x800EF228 = 0;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_800A2FB0\n\t"
        "addu $4,$zero,$zero\n\t"
        ".set reorder"
        :
        : "r"(setting)
        : "$4", "memory"
    );
    *(int *)0x800EF204 = 0;
    *(short *)0x800EF224 = 0;
    *(int *)0x800EF210 = 0;
    asm volatile("lw $31,16($sp)" : : : "memory");
}
