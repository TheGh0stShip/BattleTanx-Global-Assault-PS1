typedef int (*Callback)(int kind, int value);

int func_80094480(int value)
{
    volatile char outgoing[20];
    register Callback callback asm("$2");
    register int argument asm("$5");

    asm volatile("" : : : "memory");
    callback = *(Callback *)0x800B6B00;
    asm volatile("" : "+r"(callback) : : "memory");
    asm("addu %0,%1,$zero" : "=r"(argument) : "r"(value));
    asm volatile("sw $31,16($sp)" : : "r"(callback), "r"(argument) : "memory");
    callback = *(Callback *)((char *)callback + 0x14);
    asm volatile(
        ".set noreorder\n\t"
        "nop\n\t"
        "jalr $2\n\t"
        "addiu $4,$zero,4\n\t"
        ".set reorder"
        : "+r"(callback)
        : "r"(argument)
        : "$4", "memory"
    );
    asm volatile("lw $31,16($sp)" : : : "memory");
    return (int)callback;
}
