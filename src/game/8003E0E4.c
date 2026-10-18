typedef struct { short m[3][3]; short pad; int t[3]; } Matrix;
extern void func_8008DAA8(int *, int *);

static inline void gte_SetRotMatrix(Matrix *r)
{
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     : : "r"(r) : "$12", "$13", "$14");
}

static inline void gte_ldclmv(short *v)
{
    __asm__ volatile("lhu $12, 0(%0)\n\tlhu $13, 6(%0)\n\tlhu $14, 12(%0)\n\tmtc2 $12, $9\n\tmtc2 $13, $10\n\tmtc2 $14, $11"
                     : : "r"(v) : "$12", "$13", "$14");
}

static inline void gte_rtir(void)
{
    __asm__ volatile("nop\n\tnop\n\tcop2 0x049E012");
}

static inline void gte_stclmv(short *v)
{
    __asm__ volatile("mfc2 $12, $9\n\tmfc2 $13, $10\n\tmfc2 $14, $11\n\tsh $12, 0(%0)\n\tsh $13, 6(%0)\n\tsh $14, 12(%0)"
                     : : "r"(v) : "$12", "$13", "$14", "memory");
}

void func_8003E0E4(Matrix *rot, Matrix *in, Matrix *out)
{
    gte_SetRotMatrix(rot);
    gte_ldclmv(&in->m[0][0]);
    gte_rtir();
    gte_stclmv(&out->m[0][0]);
    gte_ldclmv(&in->m[0][1]);
    gte_rtir();
    gte_stclmv(&out->m[0][1]);
    gte_ldclmv(&in->m[0][2]);
    gte_rtir();
    gte_stclmv(&out->m[0][2]);
    func_8008DAA8(in->t, out->t);
}
