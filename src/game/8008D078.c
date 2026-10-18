void func_8008D078(const int *values) {
    asm("lw $8,0($4)\n\tlw $9,4($4)\n\tlw $10,8($4)\n\tlw $11,12($4)\n\tlw $12,16($4)\n\t"
        "ctc2 $8,$16\n\tctc2 $9,$17\n\tctc2 $10,$18\n\tctc2 $11,$19\n\tctc2 $12,$20"
        : : "r"(values));
}
