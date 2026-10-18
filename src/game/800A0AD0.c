extern void func_800943F0(void);
extern void func_80094420(int kind, const void *value);
extern char D_800A105C[];

void func_800A0AD0(void)
{
    volatile char outgoing[16];
    register const void *value asm("$5");

    *(int *)0x800B8D28 = 0;
    *(int *)0x800B8D24 = 0;
    *(int *)0x800B8D38 = 0;
    asm volatile(
        ".set noreorder\n\t"
        "lui $1,0x800C\n\t"
        "jal func_800943F0\n\t"
        "sw $zero,-0x72CC($1)\n\t"
        ".set reorder"
        :
        :
        : "$1", "$31", "memory"
    );
    value = D_800A105C;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_80094420\n\t"
        "addiu $4,$zero,2\n\t"
        ".set reorder"
        :
        : "r"(value)
        : "$4", "$31", "memory"
    );
}
