void func_8008B844(const int *values) {
    asm("lw $8,0($4)\n\tlw $9,4($4)\n\tctc2 $8,$0\n\tctc2 $9,$1\n\t"
        "lw $8,8($4)\n\tlw $9,12($4)\n\tctc2 $8,$2\n\tctc2 $9,$3\n\t"
        "lw $8,16($4)\n\tlw $9,20($4)\n\tctc2 $8,$4\n\tctc2 $9,$5\n\t"
        "lw $8,24($4)\n\tlw $9,28($4)\n\tctc2 $8,$6\n\tctc2 $9,$7"
        : : "r"(values));
}
