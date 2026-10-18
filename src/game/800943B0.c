extern int func_8009D0AC(int channel, const char *format, char *arguments);

int func_800943B0(
    const char * volatile format,
    int arg1,
    int arg2,
    int arg3
)
{
    volatile char outgoing[16];
    register char *arguments asm("$2") = (char *)&arg1;
    register int channel asm("$4") = 1;
    register const char *saved_format asm("$5");

    asm("" : "+r"(arguments));
    *(volatile int *)(arguments + 4) = arg2;
    *(volatile int *)(arguments + 8) = arg3;
    saved_format = format;
    asm volatile(
        ".set noreorder\n\t"
        "jal func_8009D0AC\n\t"
        "addu $6,$2,$zero\n\t"
        ".set reorder"
        : "+r"(arguments)
        : "r"(channel), "r"(saved_format)
        : "$6", "$31", "memory"
    );

    return (int)arguments;
}
