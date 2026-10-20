extern int D_800B7BC0;
extern int D_800B7758;
extern unsigned char D_8009A4BC[];
extern void func_80094198(void);
extern void func_800A2F60(void *value);
extern int func_80094158(unsigned int mode, unsigned int count,
                         unsigned int size, unsigned int unused);
extern void func_800940B4(int value);
extern int func_80094168(void);

void func_8009AB5C(void) __attribute__((noreturn));

void func_8009AB5C(void) {
    int handle;

    if (D_800B7BC0 == 0) {
        {
            register int one asm("$2") = 1;
            asm volatile(".set\tnoreorder\n\t"
                         "lui $1,%%hi(D_800B7BC0)\n\t"
                         "jal func_80094198\n\t"
                         "sw %0,%%lo(D_800B7BC0)($1)\n\t"
                         ".set\treorder"
                         : : "r"(one) : "$1", "$31", "memory");
        }
        func_800A2F60(D_8009A4BC);
        handle = func_80094158(0xF0000009U, 32, 0x2000, 0);
        {
            register int argument asm("$4") = handle;
            asm volatile(".set\tnoreorder\n\t"
                         "lui $1,%%hi(D_800B7758)\n\t"
                         "jal func_800940B4\n\t"
                         "sw %0,%%lo(D_800B7758)($1)\n\t"
                         ".set\treorder"
                         : : "r"(argument) : "$1", "$31", "memory");
        }
        func_80094168();
    }
    asm volatile("lw $31,16($29)\n\t"
                 "addiu $29,$29,24\n\t"
                 "jr $31\n\t"
                 "nop\n\t"
                 ".macro lw args:vararg\n\t"
                 ".word 0\n\t"
                 ".endm\n\t"
                 ".macro j args:vararg\n\t"
                 ".word 0\n\t"
                 ".endm\n\t"
                 ".macro addu args:vararg\n\t"
                 ".word 0\n\t"
                 ".endm");
}
