void func_80085B68(unsigned char *cursor, void **start_out,
                   unsigned int *value_out) {
    register int marker asm("$3");

    asm volatile(
        ".set noreorder\n\t"
        "lw $3, -4(%0)\n\t"
        "addiu $2, $zero, -1\n\t"
        "bne $3, $2, 1f\n\t"
        "addu $3, $2, $zero\n\t"
        "addiu %0, %0, -4\n\t"
        "2:\n\t"
        "lw $2, -4(%0)\n\t"
        "nop\n\t"
        "beq $2, $3, 2b\n\t"
        "addiu %0, %0, -4\n\t"
        "addiu %0, %0, 4\n"
        "1:\n\t"
        ".set reorder"
        : "+r"(cursor)
        :
        : "$2", "$3");

    {
        register unsigned char *header asm("$2") = cursor - 12;

        asm("" : "+r"(header));
        marker = *(int *)(header + 8);
    }
    if (start_out != 0) {
        *start_out = cursor;
    }
    if (value_out != 0) {
        *value_out = marker;
    }
}
