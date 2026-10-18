void func_8008D028(const int *values) {
    asm("lw $8,0($4)\n\tlw $9,4($4)\n\tlw $10,8($4)\n\tlw $11,12($4)\n\tlw $12,16($4)\n\t"
        "ctc2 $8,$8\n\tctc2 $9,$9\n\tctc2 $10,$10\n\tctc2 $11,$11\n\tctc2 $12,$12"
        : : "r"(values));
}
