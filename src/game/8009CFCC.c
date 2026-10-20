typedef struct BufferRecord {
    short state;
    unsigned char unused2[4];
    unsigned short count;
    unsigned char unused8[24];
} BufferRecord;

extern BufferRecord *D_800EF230;
extern int D_800EF23C;
extern int D_800EF240;

int func_8009CFCC(void *data) {
    register void *input asm("$4") = data;
    register int index asm("$5");
    register int offset asm("$4");
    register int result asm("$2");
    register int count asm("$3");
    register int count_limit asm("$6");

    asm volatile("lui $5,0x8208\n\t"
                 "ori $5,$5,0x2083\n\t"
                 "lui $2,%%hi(D_800EF240)\n\t"
                 "lw $2,%%lo(D_800EF240)($2)\n\t"
                 "lui $3,%%hi(D_800EF230)\n\t"
                 "lw $3,%%lo(D_800EF230)($3)\n\t"
                 "sll $2,$2,5\n\t"
                 "addu $2,$3,$2\n\t"
                 "subu $4,$4,$2\n\t"
                 "sra $2,$4,2\n\t"
                 "mult $2,$5\n\t"
                 "sra $4,$4,31\n\t"
                 "mfhi $7\n\t"
                 "addu $2,$7,$2\n\t"
                 "sra $2,$2,8\n\t"
                 "subu $5,$2,$4\n\t"
                 "sll $2,$5,5\n\t"
                 "addu $3,$3,$2"
                 : "+r"(input), "=r"(index), "=r"(result), "=r"(count)
                 : : "$7", "hi", "lo", "memory");
    result = ((BufferRecord *)count)->state;
    count = ((BufferRecord *)count)->count;
    if (result != 4) {
        result = 1;
        goto done;
    }
    result = (short)count;
    offset = 0;
    if (result > 0) {
        count_limit = result;
        asm volatile("1:\n\t"
                     "addu $2,$4,$5\n\t"
                     "addiu $4,$4,1\n\t"
                     "lui $3,%%hi(D_800EF230)\n\t"
                     "lw $3,%%lo(D_800EF230)($3)\n\t"
                     "sll $2,$2,5\n\t"
                     "addu $3,$3,$2\n\t"
                     "slt $2,$4,$6\n\t"
                     "bnez $2,1b\n\t"
                     "sh $0,0($3)"
                     : "+r"(offset), "+r"(result), "+r"(count)
                     : "r"(index), "r"(count_limit) : "memory");
    }
    asm volatile("addu $2,$4,$5\n\t"
                 "lui $1,%%hi(D_800EF23C)\n\t"
                 "sw $2,%%lo(D_800EF23C)($1)\n\t"
                 "addu $2,$0,$0"
                 : "=r"(result) : "r"(offset), "r"(index) : "$1", "memory");
done:
    asm volatile("" : "+r"(result));
    return result;
}
