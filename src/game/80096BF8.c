extern int D_800EF060;
extern int D_800EF064;
extern int D_800EF068;
extern int D_800EF06C;
extern volatile int D_800EF070;
extern volatile int D_800EF074;
extern volatile int D_800EF078;
extern volatile int D_800EF07C;
extern void func_8009AED4(int value);

int func_80096BF8(void) {
    register int result asm("$16");
    register int return_value asm("$2");
    register int argument asm("$4");

    asm volatile("1:\n\t"
                 "lui $2,%%hi(D_800EF074)\n\t"
                 "lw $2,%%lo(D_800EF074)($2)\n\t"
                 "lui $4,%%hi(D_800EF070)\n\t"
                 "lw $4,%%lo(D_800EF070)($4)\n\t"
                 "lui $3,%%hi(D_800EF078)\n\t"
                 "lw $3,%%lo(D_800EF078)($3)\n\t"
                 "sll $2,$2,1\n\t"
                 "addu $4,$4,$2\n\t"
                 "sll $3,$3,2\n\t"
                 "lui $2,%%hi(D_800EF07C)\n\t"
                 "lw $2,%%lo(D_800EF07C)($2)\n\t"
                 "addu $4,$4,$3\n\t"
                 "sll $2,$2,3\n\t"
                 "addu %0,$4,$2\n\t"
                 "beqz %0,1b\n\t"
                 "nop" : "=r"(result) : : "$2", "$3", "$4", "memory");
    asm volatile("lui %0,%%hi(D_800EF060)\n\t"
                 "lw %0,%%lo(D_800EF060)(%0)" : "=r"(argument));
    func_8009AED4(argument);
    asm volatile("lui %0,%%hi(D_800EF064)\n\t"
                 "lw %0,%%lo(D_800EF064)(%0)" : "=r"(argument));
    func_8009AED4(argument);
    asm volatile("lui %0,%%hi(D_800EF068)\n\t"
                 "lw %0,%%lo(D_800EF068)(%0)" : "=r"(argument));
    func_8009AED4(argument);
    asm volatile("lui %0,%%hi(D_800EF06C)\n\t"
                 "lw %0,%%lo(D_800EF06C)(%0)" : "=r"(argument));
    func_8009AED4(argument);
    asm volatile("lui $1,%%hi(D_800EF07C)\n\t"
                 "sw $0,%%lo(D_800EF07C)($1)\n\t"
                 "lui $2,%%hi(D_800EF07C)\n\t"
                 "lw $2,%%lo(D_800EF07C)($2)\n\t"
                 "lui $1,%%hi(D_800EF078)\n\t"
                 "sw $2,%%lo(D_800EF078)($1)\n\t"
                 "lui $2,%%hi(D_800EF078)\n\t"
                 "lw $2,%%lo(D_800EF078)($2)\n\t"
                 "lui $1,%%hi(D_800EF074)\n\t"
                 "sw $2,%%lo(D_800EF074)($1)\n\t"
                 "lui $3,%%hi(D_800EF074)\n\t"
                 "lw $3,%%lo(D_800EF074)($3)\n\t"
                 "sra %0,%1,1\n\t"
                 "lui $1,%%hi(D_800EF070)\n\t"
                 "sw $3,%%lo(D_800EF070)($1)"
                 : "=r"(return_value) : "r"(result) : "$1", "$3", "memory");
    return return_value;
}
