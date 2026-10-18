extern void func_8008163C(void);
extern int func_80094450(int kind, void (*callback)(void));

int func_80081E3C(void)
{
    volatile char outgoing[16];
    register void (*callback)(void) asm("$5");
    register int result asm("$2");

    asm volatile("" : : : "$31", "memory");
    callback = func_8008163C;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_80094450\n\t"
        "addiu $4,$zero,2\n\t"
        ".set reorder"
        : "=r"(result)
        : "r"(callback)
        : "$4", "$31", "memory"
    );
    return result;
}
