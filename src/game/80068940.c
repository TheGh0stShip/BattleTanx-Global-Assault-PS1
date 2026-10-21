typedef struct Matrix {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

int func_8008ACC0(int);
int func_8008AD60(int);


void func_80068940(Matrix *out, Matrix *in, short angle) {
    register int r10 __asm__("$10");
    register int r11 __asm__("$11");
    register int r12 __asm__("$12");
    register int r13 __asm__("$13");
    register int r14 __asm__("$14");
    register int r15 __asm__("$15");
    int s;
    int *ow = (int *)out;
    int *iw = (int *)in;
    unsigned short *oh = (unsigned short *)out;

    if (angle != 0) {

        s = func_8008AD60(angle);
        r14 = func_8008ACC0(angle) & 0xFFFF;
        __asm__("neg %0, %1" : "=r"(r12) : "r"(s));
        r12 = (r12 << 16) | r14;
        r13 = s << 16;
        r15 = 4096;
        ow[0] = r12;
        ow[1] = r13;
        ow[2] = r14;
        ow[3] = 0;
        ow[4] = r15;


        r13 = iw[0];
        r14 = iw[1];
        r15 = iw[2];
        r10 = oh[0];
        r11 = oh[3];
        r12 = oh[6];
        __asm__ volatile("ctc2 %0, $0" : : "r"(r13));
        r13 = iw[3];
        __asm__ volatile("mtc2 %0, $9" : : "r"(r10));
        r10 = iw[4];
        __asm__ volatile("ctc2 %0, $1" : : "r"(r14));
        __asm__ volatile("ctc2 %0, $2" : : "r"(r15));
        __asm__ volatile("mtc2 %0, $10" : : "r"(r11));
        __asm__ volatile("mtc2 %0, $11" : : "r"(r12));
        __asm__ volatile("ctc2 %0, $3" : : "r"(r13));
        __asm__ volatile("ctc2 %0, $4" : : "r"(r10));
        __asm__ volatile("nop\n\tnop\n\tcop2 0x049E012");


        r10 = oh[1];
        r11 = oh[4];
        r12 = oh[7];
        __asm__ volatile("mfc2 %0, $9" : "=r"(r13));
        __asm__ volatile("mfc2 %0, $10" : "=r"(r14));
        __asm__ volatile("mfc2 %0, $11" : "=r"(r15));
        __asm__ volatile("mtc2 %0, $9" : : "r"(r10));
        __asm__ volatile("mtc2 %0, $10" : : "r"(r11));
        __asm__ volatile("mtc2 %0, $11" : : "r"(r12));
        r10 = oh[2];
        r11 = oh[5];
        r12 = oh[8];
        __asm__ volatile("cop2 0x049E012");
        oh[0] = r13;
        oh[3] = r14;
        oh[6] = r15;


        __asm__ volatile("mfc2 %0, $9" : "=r"(r13));
        __asm__ volatile("mfc2 %0, $10" : "=r"(r14));
        __asm__ volatile("mfc2 %0, $11" : "=r"(r15));
        __asm__ volatile("mtc2 %0, $9" : : "r"(r10));
        __asm__ volatile("mtc2 %0, $10" : : "r"(r11));
        __asm__ volatile("mtc2 %0, $11" : : "r"(r12));
        oh[1] = r13;
        oh[4] = r14;
        oh[7] = r15;
        __asm__ volatile("cop2 0x049E012");
        r10 = ow[0];
        r12 = ow[3];
        __asm__ volatile("mfc2 %0, $9" : "=r"(r13));
        __asm__ volatile("mfc2 %0, $10" : "=r"(r14));
        __asm__ volatile("mfc2 %0, $11" : "=r"(r15));
        oh[2] = r13;
        oh[5] = r14;
        oh[8] = r15;
        __asm__ volatile("");


        r11 = ow[1];
        r13 = ow[2];
        r14 = ow[4];
        __asm__ volatile("ctc2 %0, $0" : : "r"(r10));
        __asm__ volatile("ctc2 %0, $1" : : "r"(r11));
        __asm__ volatile("ctc2 %0, $3" : : "r"(r12));
        __asm__ volatile("ctc2 %0, $2" : : "r"(r13));
        __asm__ volatile("ctc2 %0, $4" : : "r"(r14));
    } else {

        r12 = iw[0];
        r13 = iw[1];
        __asm__ volatile("ctc2 %0, $0" : : "r"(r12));
        __asm__ volatile("ctc2 %0, $1" : : "r"(r13));
        r12 = iw[2];
        r13 = iw[3];
        r14 = iw[4];
        __asm__ volatile("ctc2 %0, $2" : : "r"(r12));
        __asm__ volatile("ctc2 %0, $3" : : "r"(r13));
        __asm__ volatile("ctc2 %0, $4" : : "r"(r14));
    }
}
