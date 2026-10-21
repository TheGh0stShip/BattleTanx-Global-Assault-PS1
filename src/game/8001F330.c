typedef struct Rec {
    unsigned char flag;
    unsigned char cur;
    char pad2[4];
    unsigned short heading;
    char pad8[4];
    int x;
    int pad10;
    int z;
    char pad18[156 - 24];
} Rec;

extern Rec D_800D3034[];
extern short D_800D5B88;

static inline int div4096_pos(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline int div4096(int v) {
    if (v < 0) {
        return -(-v >> 12);
    }
    return v >> 12;
}

static inline int table_sine(int angle_in) {
    register int angle asm("$4");
    register int quadrant asm("$8");
    register int index asm("$9");
    int value;

    angle = angle_in;
    __asm__ volatile("");
    quadrant = angle & 0x4000;
    __asm__ volatile("andi $9, %1, 0x3fff" : "=r"(index) : "r"(angle));
    if (quadrant != 0) {
        __asm__ volatile("");
        quadrant = 16383;
        __asm__ volatile("sub $9, $8, $9" : "+r"(index) : "r"(quadrant));
    }
    index &= 0x3ffe;
    __asm__ volatile("lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)" : "+r"(index));
    quadrant = angle & 0x8000;
    if (quadrant != 0) {
        __asm__ volatile("neg $9, $9" : "+r"(index));
    }
    __asm__ volatile("sll %0, $9, 1" : "=r"(value) : "r"(index));
    return value;
}

static inline int table_cosine(int angle) {
    register int quadrant asm("$8");
    register int index asm("$9");
    register int turned asm("$10");
    register int value asm("$2");

    __asm__ volatile("addiu $10, %3, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff"
                     : "=r"(turned), "=r"(quadrant), "=r"(index) : "r"(angle));
    if (quadrant != 0) {
        __asm__ volatile("");
        quadrant = 16383;
        __asm__ volatile("sub $9, $8, $9" : "+r"(index) : "r"(quadrant));
    }
    index &= 0x3ffe;
    __asm__ volatile("lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)" : "+r"(index));
    quadrant = turned & 0x8000;
    if (quadrant != 0) {
        __asm__ volatile("neg $9, $9" : "+r"(index));
    }
    __asm__ volatile("sll %0, $9, 1" : "=r"(value) : "r"(index));
    return value;
}
static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

int abs(int);

static inline int fixed_div(int numer, int denominator) {
    register int numerator asm("$6") = numer;
    register int negative asm("$9");
    register int n asm("$2");
    register int m asm("$3");
    register int sign asm("$3");
    register int d asm("$7");
    register int n_zeros asm("$4");
    register int d_zeros asm("$6");
    register int excess asm("$8");
    int scale;
    unsigned int quotient;
    register int dsign asm("$2");
    register unsigned int dv asm("$2");
    int result;

    sign = numerator & 0x80000000;
    dsign = denominator & 0x80000000;
    negative = sign ^ dsign;
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        m = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                dv = d >> scale;
            } else {
                dv = d << -scale;
            }
            quotient = (unsigned int)m / dv;
            quotient <<= n_zeros;
        } else {
            dv = d >> -excess;
            quotient = (unsigned int)m / dv;
        }
    } else {
        m = n << 12;
        quotient = (unsigned int)m / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int scaled(int r, int s) {
    return (r * s) >> 16;
}

static inline void project(int angle, int r, int *out, int k) {
    register int a asm("$4");
    register int quadrant asm("$8");
    register int index asm("$9");
    register int turned asm("$10");
    int value;

    a = angle;
    out[k] = out[4] + scaled(r, table_sine(a));
    __asm__ volatile("addiu $10, %3, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff"
                     : "=r"(turned), "=r"(quadrant), "=r"(index) : "r"(a));
    if (quadrant != 0) {
        __asm__ volatile("");
        quadrant = 16383;
        __asm__ volatile("sub $9, $8, $9" : "+r"(index) : "r"(quadrant));
    }
    index &= 0x3ffe;
    __asm__ volatile("lui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)" : "+r"(index));
    quadrant = turned & 0x8000;
    if (quadrant != 0) {
        __asm__ volatile("neg $9, $9" : "+r"(index));
    }
    __asm__ volatile("sll %0, $9, 1" : "=r"(value) : "r"(index));
    out[k + 1] = out[5] + scaled(r, value);
}

void func_8001F330(int fov, int *out) {
    Rec *e;
    int half;
    int heading;
    register int left asm("$11");
    register int right asm("$12");
    register int c asm("$4");
    int r;
    register int num asm("$3");
    register int span asm("$3");
    register int hs asm("$2");
    register int cv asm("$2");

    e = &D_800D3034[D_800D3034[0].cur];
    heading = e->heading;
    out[4] = div4096_pos(e->x);
    out[5] = div4096(D_800D3034[D_800D3034[0].cur].z);
    half = (unsigned int)(fov << 16) / 360;
    hs = (short)heading;
    span = (unsigned short)half;
    left = hs + span;
    left = (unsigned short)left;
    right = hs - span;
    right = (unsigned short)right;
    num = D_800D5B88;
    cv = table_cosine(half);
    c = cv >> 4;
    if (c == 0) {
        c = 2;
    }
    r = div4096(fixed_div(num << 12, c));
    project(left, r, out, 0);
    project(right, r, out, 2);
}
