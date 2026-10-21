typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

extern int func_8008AD60(int angle);
extern int func_8008ACC0(int angle);
extern void func_80068CA8(Matrix *a, Matrix *b);

void func_800687CC(Matrix *out_arg, Matrix *base_arg, short angle) {
    register Matrix *out asm("$17") = out_arg;
    register Matrix *base asm("$18") = base_arg;
    int s;
    int c;

    if (angle != 0) {
        s = func_8008AD60(angle);
        c = func_8008ACC0(angle);
        __asm__ volatile("li $12, 4096\n\tandi $15, %2, 0xffff\n\tneg $13, %1\n\tsll $13, $13, 16\n\tor $13, $13, $15\n\t"
                         "sll $14, %1, 16\n\tsw $12, 0(%0)\n\tsw $0, 4(%0)\n\tsw $13, 8(%0)\n\tsw $14, 12(%0)\n\tsw $15, 16(%0)"
                         : : "r"(out), "r"(s), "r"(c) : "$12", "$13", "$14", "$15", "memory");
        func_80068CA8(out, base);
    } else {
        register int *p asm("$18") = (int *)base;
        register int r0 asm("$12");
        register int r1 asm("$13");
        register int r2 asm("$14");

        __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1" : : "r"(p) : "$12", "$13");
        r0 = p[2];
        r1 = p[3];
        r2 = p[4];
        __asm__ volatile("ctc2 %0, $2\n\tctc2 %1, $3\n\tctc2 %2, $4" : : "r"(r0), "r"(r1), "r"(r2));
    }
}
