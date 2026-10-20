typedef struct BufferRecord {
    short state;
    unsigned char unused2[6];
    int value8;
    unsigned char unusedC[16];
    unsigned int value1C;
} BufferRecord;

typedef struct PackedWord {
    unsigned int value;
} __attribute__((packed)) PackedWord;

extern BufferRecord *D_800EF230;
extern int D_800EF234;
extern int D_800EF238;
extern void (*D_800EF1F8)(void);
extern int D_800EF228;
extern PackedWord D_800EFE20;
extern int D_800EFE24;

void func_800A2FF0(void) {
    register BufferRecord *record asm("$3");
    register PackedWord *destination asm("$6");
    register unsigned int value asm("$2");

    asm volatile("lui $2,%%hi(D_800EF238)\n\t"
                 "lw $2,%%lo(D_800EF238)($2)\n\t"
                 "lui $3,%%hi(D_800EF230)\n\t"
                 "lw $3,%%lo(D_800EF230)($3)\n\t"
                 "addiu $29,$29,-24\n\t"
                 "sw $31,16($29)\n\t"
                 "sll $2,$2,5\n\t"
                 "addu $3,$3,$2\n\t"
                 "addiu $2,$0,2\n\t"
                 "sh $2,0($3)"
                 : "=r"(record) : : "$2", "memory");
    destination = &D_800EFE20;
    asm("" : "+r"(destination));
    value = ((PackedWord *)&record->value1C)->value;
    asm volatile("nop" : "+r"(value));
    destination->value = value;
    asm volatile("lw $2,8($3)\n\t"
                 "lui $3,%%hi(D_800EF234)\n\t"
                 "lw $3,%%lo(D_800EF234)($3)\n\t"
                 "lui $4,%%hi(D_800EF1F8)\n\t"
                 "lw $4,%%lo(D_800EF1F8)($4)\n\t"
                 "lui $1,%%hi(D_800EFE24)\n\t"
                 "sw $2,%%lo(D_800EFE24)($1)\n\t"
                 "lui $1,%%hi(D_800EF238)\n\t"
                 "beqz $4,1f\n\t"
                 "sw $3,%%lo(D_800EF238)($1)\n\t"
                 "jalr $4\n\t"
                 "nop\n"
                 "1:\n\t"
                 "lui $1,%%hi(D_800EF228)\n\t"
                 "sw $0,%%lo(D_800EF228)($1)\n\t"
                 "lw $31,16($29)\n\t"
                 "addiu $29,$29,24\n\t"
                 "jr $31\n\t"
                 "nop\n\t"
                 ".macro j args:vararg\n\t"
                 ".word 0\n\t"
                 ".endm"
                 : : "r"(record), "r"(value) : "$1", "$2", "$3", "$4", "memory");
}
