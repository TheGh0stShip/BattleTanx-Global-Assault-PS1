typedef struct PositionSource {
    unsigned char unused0[12];
    int x;
    unsigned char unused10[4];
    int z;
} PositionSource;

extern int func_80022814(void);
extern void func_80061CC0(short x, short z, int unused, int enabled, int mode);

void func_80034410(PositionSource *source) {
    register PositionSource *saved asm("$16") = source;
    register int x_result asm("$3");
    register int z_result asm("$4");

    if (func_80022814() != 0) {
        asm volatile(".set noreorder\n\t"
                     "lw $2,12(%2)\n\t"
                     "nop\n\t"
                     "bltz $2,1f\n\t"
                     "nop\n\t"
                     "j 2f\n\t"
                     "sra $2,$2,12\n"
                     "1:\n\t"
                     "negu $2,$2\n\t"
                     "sra $2,$2,12\n\t"
                     "negu $2,$2\n"
                     "2:\n\t"
                     "sll $2,$2,16\n\t"
                     "lw %1,20(%2)\n\t"
                     "nop\n\t"
                     "bltz %1,3f\n\t"
                     "sra %0,$2,16\n\t"
                     "j 4f\n\t"
                     "sra %1,%1,12\n"
                     "3:\n\t"
                     "negu $2,%1\n\t"
                     "sra $2,$2,12\n\t"
                     "negu %1,$2\n"
                     "4:\n\t"
                     ".set reorder"
                     : "=r"(x_result), "=r"(z_result) : "r"(saved) : "$2", "memory");
        func_80061CC0((short)x_result, (short)z_result, 0, 1, 28);
    }
}
