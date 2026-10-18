extern void func_80096810(void);

void func_80094D9C(void)
{
    volatile char outgoing[16];

    *(int *)0x800EF090 = 0;
    asm volatile(
        ".set noreorder\n\t"
        "lui $1,0x800F\n\t"
        "jal func_80096810\n\t"
        "sw $zero,-0x0F2C($1)\n\t"
        ".set reorder"
        :
        :
        : "$1", "$31", "memory"
    );
}
