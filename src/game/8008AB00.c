typedef struct Vector16 {
    short x;
    short y;
    short z;
} Vector16;

extern void func_8008AB30(void);

void func_8008AB00(const Vector16 *input, Vector16 *output)
{
    register int x asm("$8") = input->x;
    register int y asm("$9") = input->y;
    register int z asm("$10") = input->z;
    register unsigned int saved_return asm("$7");

    asm volatile(
        ".set noreorder\n\t"
        "addu $7,$31,$zero\n\t"
        "jal func_8008AB30\n\t"
        "nop\n\t"
        ".set reorder"
        : "+r"(x), "+r"(y), "+r"(z), "=r"(saved_return)
        :
        : "memory"
    );
    output->x = x;
    output->y = y;
    output->z = z;
    asm volatile("addu $31,$7,$zero" : : "r"(saved_return) : "memory");
}
