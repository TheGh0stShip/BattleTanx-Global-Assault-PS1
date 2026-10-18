short *func_80098870(const int *matrix, const int *vector, short *output) {
    asm("lw $8,0($4)\n\tlw $9,4($4)\n\tlw $10,8($4)\n\tlw $11,12($4)\n\tlw $12,16($4)\n\t"
        "ctc2 $8,$0\n\tctc2 $9,$1\n\tctc2 $10,$2\n\tctc2 $11,$3\n\tctc2 $12,$4\n\t"
        "lwc2 $0,0($5)\n\tlwc2 $1,4($5)\n\tnop\n\t.word 0x4A486012\n\t"
        "mfc2 $8,$9\n\tmfc2 $9,$10\n\tmfc2 $10,$11\n\t"
        "sh $8,0($6)\n\tsh $9,2($6)\n\tsh $10,4($6)"
        : : "r"(matrix), "r"(vector), "r"(output) : "$2", "memory");
    {
        register short *result asm("$2") = output;

        asm("" : "+r"(result));
        asm volatile("" : : : "memory");
        return result;
    }
}
