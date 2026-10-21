typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

extern Matrix *D_800E5374;
extern int func_8008AD60(int angle);
extern int func_8008ACC0(int angle);

static inline void set_rot_matrix(Matrix *m)
{
    register unsigned int r0 asm("$12");
    register unsigned int r1 asm("$13");
    register unsigned int r2 asm("$14");

    r0 = ((unsigned int *)m)[0];
    r1 = ((unsigned int *)m)[1];
    __asm__ volatile("ctc2 %0, $0\n\tctc2 %1, $1" : : "r"(r0), "r"(r1));
    r0 = ((unsigned int *)m)[2];
    r1 = ((unsigned int *)m)[3];
    r2 = ((unsigned int *)m)[4];
    __asm__ volatile("ctc2 %0, $2\n\tctc2 %1, $3\n\tctc2 %2, $4" : : "r"(r0), "r"(r1), "r"(r2));
}

static inline void rot_column(short *col)
{
    register unsigned int r0 asm("$12");
    register unsigned int r1 asm("$13");
    register unsigned int r2 asm("$14");

    r0 = (unsigned short)col[0];
    r1 = (unsigned short)col[3];
    r2 = (unsigned short)col[6];
    __asm__ volatile("mtc2 %0, $9\n\tmtc2 %1, $10\n\tmtc2 %2, $11" : : "r"(r0), "r"(r1), "r"(r2));
    __asm__ volatile("nop\n\tnop\n\tcop2 0x49E012");
    __asm__ volatile("mfc2 %0, $9\n\tmfc2 %1, $10\n\tmfc2 %2, $11" : "=r"(r0), "=r"(r1), "=r"(r2));
    col[0] = r0;
    col[3] = r1;
    col[6] = r2;
}

void func_80068AE4(Matrix *m, int unused, short angle)
{
    if (angle != 0) {
        int s = func_8008AD60(angle);
        int c = func_8008ACC0(angle);
        register unsigned int r0 asm("$12");
        register unsigned int r1 asm("$13");
        register unsigned int r2 asm("$14");
        register unsigned int r3 asm("$15");
        short *col;

        r0 = c & 0xFFFF;
        r1 = s & 0xFFFF;
        r2 = 4096;
        __asm__("neg %0, %1" : "=r"(r3) : "r"(s));
        r3 &= 0xFFFF;
        ((unsigned int *)m)[0] = r0;
        ((unsigned int *)m)[1] = r1;
        ((unsigned int *)m)[2] = r2;
        ((unsigned int *)m)[3] = r3;
        ((unsigned int *)m)[4] = r0;
        __asm__ volatile("" : : : "memory");
        set_rot_matrix(D_800E5374);
        rot_column(&m->m[0][0]);
        __asm__ volatile("" : : : "memory");
        col = &m->m[0][1];
        __asm__("" : "=r"(col) : "0"(col));
        rot_column(col);
        __asm__ volatile("" : : : "memory");
        col = &m->m[0][2];
        __asm__("" : "=r"(col) : "0"(col));
        rot_column(col);
        set_rot_matrix(m);
    } else {
        set_rot_matrix(D_800E5374);
    }
}
