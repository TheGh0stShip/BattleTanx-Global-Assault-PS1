typedef struct BufferRecord {
    unsigned short state;
    unsigned char unused2[30];
} BufferRecord;

extern BufferRecord *D_800EF230;
extern int D_800EF218;
extern int D_800EF23C;
extern int D_800EF240;

int func_8009CF0C(void **output_data, BufferRecord **output_record) {
    register void **data_out asm("$7") = output_data;
    register BufferRecord **record_out asm("$8");
    register BufferRecord *record asm("$6");
    register int state asm("$3");
    register int result asm("$2");

    asm("" : "+r"(data_out));
    {
        register int index asm("$2");
        register BufferRecord *base asm("$3");
        asm volatile("lui %0,%%hi(D_800EF23C)\n\t"
                     "lw %0,%%lo(D_800EF23C)(%0)"
                     : "=r"(index) : : "memory");
        asm volatile("lui %0,%%hi(D_800EF230)\n\t"
                     "lw %0,%%lo(D_800EF230)(%0)"
                     : "=r"(base) : : "memory");
        asm volatile("sll %0,%0,5\n\t"
                     "addu %1,%2,%0"
                     : "+r"(index), "=r"(record) : "r"(base));
    }
    state = record->state;
    asm volatile(".set\tnoreorder\n\t"
                 "addiu $2,$0,1\n\t"
                 "bne $3,$2,.L8009CF0C_after_state_one\n\t"
                 "addu $8,$5,$0\n\t"
                 ".set\treorder"
                 : "=r"(result), "=r"(record_out) : "r"(state), "r"(output_record));
    asm volatile("lui $2,%%hi(D_800EF218)\n\t"
                 "lw $2,%%lo(D_800EF218)($2)\n\t"
                 "lui $1,%%hi(D_800EF23C)\n\t"
                 "beqz $2,1f\n\t"
                 "sw $0,%%lo(D_800EF23C)($1)\n\t"
                 "sh $0,0($6)\n"
                 "1:"
                 : : "r"(record) : "$1", "$2", "memory");
    {
        register int index asm("$2");
        register BufferRecord *base asm("$3");
        asm volatile("lui %0,%%hi(D_800EF23C)\n\t"
                     "lw %0,%%lo(D_800EF23C)(%0)"
                     : "=r"(index) : : "memory");
        asm volatile("lui %0,%%hi(D_800EF230)\n\t"
                     "lw %0,%%lo(D_800EF230)(%0)"
                     : "=r"(base) : : "memory");
        record = &base[index];
    }
    asm volatile(".L8009CF0C_after_state_one:");
    state = record->state;
    asm volatile(".set\tnoreorder\n\t"
                 "addiu $2,$0,2\n\t"
                 "bne $3,$2,.L8009CF0C_done\n\t"
                 "addiu $2,$0,1\n\t"
                 "addiu $2,$0,4\n\t"
                 "sh $2,0($6)\n\t"
                 "addu $2,$0,$0\n\t"
                 ".set\treorder"
                 : "=r"(result) : "r"(state), "r"(record) : "memory");
    {
        register int base_index asm("$3");
        register unsigned char *base asm("$4");
        register int record_index asm("$5");
        asm volatile("lui %0,%%hi(D_800EF240)\n\t"
                     "lw %0,%%lo(D_800EF240)(%0)"
                     : "=r"(base_index) : : "memory");
        asm volatile("lui %0,%%hi(D_800EF230)\n\t"
                     "lw %0,%%lo(D_800EF230)(%0)"
                     : "=r"(base) : : "memory");
        asm volatile("lui %0,%%hi(D_800EF23C)\n\t"
                     "lw %0,%%lo(D_800EF23C)(%0)"
                     : "=r"(record_index) : : "memory");
        base += base_index << 5;
        base += record_index * 2016;
        *data_out = base;
        *record_out = record;
    }
    asm volatile(".L8009CF0C_done:" : "+r"(result));
    return result;
}
