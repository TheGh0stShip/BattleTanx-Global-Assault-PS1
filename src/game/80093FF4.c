int *func_80093FF4(const int *matrix, const int *vector, int *output) {
    asm("lw $8,0($4)\n\tlw $9,4($4)\n\tlw $10,8($4)\n\tlw $11,12($4)\n\tlw $12,16($4)\n\t"
        "ctc2 $8,$0\n\tctc2 $9,$1\n\tctc2 $10,$2\n\tctc2 $11,$3\n\tctc2 $12,$4\n\t"
        "lwc2 $0,0($5)\n\tlwc2 $1,4($5)\n\tnop\n\tcop2 0x486012\n\t"
        "swc2 $25,0($6)\n\tswc2 $26,4($6)\n\tswc2 $27,8($6)"
        : : "r"(matrix), "r"(vector), "r"(output) : "$2", "memory");
    {
        register int *result asm("$2") = output;

        asm("" : "+r"(result));
        asm volatile("" : : : "memory");
        return result;
    }
}
