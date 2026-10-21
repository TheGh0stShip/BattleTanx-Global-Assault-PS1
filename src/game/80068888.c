typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

extern int func_8008AD60(int angle);
extern int func_8008ACC0(int angle);
extern void func_80068CA8(Matrix *a, Matrix *b);

static inline void pack_rot_z(int *out, int s, int c) {
    __asm__ volatile("andi $12, %6, 0xffff\n\tandi $13, %5, 0xffff\n\tli $14, 4096\n\tneg $15, %5\n\tandi $15, $15, 0xffff\n\t"
                     "sw $12, %0\n\tsw $13, %1\n\tsw $14, %2\n\tsw $15, %3\n\tsw $12, %4"
                     : "=m"(out[0]), "=m"(out[1]), "=m"(out[2]), "=m"(out[3]), "=m"(out[4])
                     : "r"(s), "r"(c) : "$12", "$13", "$14", "$15");
}

static inline void set_rot_matrix(Matrix *m) {
    register int r0 __asm__("$12");
    register int r1 __asm__("$13");
    register int r2 __asm__("$14");
    r0 = ((int *)m)[0];
    r1 = ((int *)m)[1];
    __asm__ volatile("ctc2 %0, $0\n\tctc2 %1, $1" : : "r"(r0), "r"(r1));
    r0 = ((int *)m)[2];
    r1 = ((int *)m)[3];
    r2 = ((int *)m)[4];
    __asm__ volatile("ctc2 %0, $2\n\tctc2 %1, $3\n\tctc2 %2, $4" : : "r"(r0), "r"(r1), "r"(r2));
}

void func_80068888(Matrix *out, Matrix *base, short angle) {
    int s;
    int c;

    if (angle != 0) {
        s = func_8008AD60(angle);
        c = func_8008ACC0(angle);
        pack_rot_z((int *)out, s, c);
        func_80068CA8(out, base);
    } else {
        set_rot_matrix(base);
    }
}
