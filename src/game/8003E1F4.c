typedef struct { short m[3][3]; short pad; int t[3]; } Matrix;
typedef struct { char pad[0x50]; Matrix rot; char pad2[156 - 0x70]; } View;
typedef struct { unsigned char f0; unsigned char current; char pad[2]; View views[1]; } ViewSet;
typedef struct { unsigned char c[20]; } SkyColors;
typedef struct { char pad[0x3C]; int *model; char pad2[72 - 0x40]; } Prop;
typedef struct { char pad[4]; int num; int den; char pad2[0x20 - 0xC]; Prop *props; char pad3[0x1B4 - 0x24]; SkyColors sky; } LevelData;
typedef struct { LevelData *data; int f4; unsigned char last_view; } Game;
typedef struct { char data[60]; } Light;
typedef struct { int ot[4098]; } OrderTable;
extern Game D_800D2FE4;
extern ViewSet D_800D3034;
extern unsigned short D_800A5B94;
extern int D_800A5B98;
extern int D_800A5B9C;
extern int D_800A5BA0;
extern int *D_800D2E00;
extern Light D_800DE0EC[2];
extern OrderTable D_800D5B94[];
extern int D_800A48B4;
extern void func_8008DC0C(void);
extern void func_8005A8C0(void);
extern void func_8006C06C(void);
extern void func_8003EB80(void);
extern int func_8008A438(int);
extern int func_8008DC84(int);
extern void func_8003E9A8(int, short);
extern void func_8006A0DC(void);
extern int func_800201C0(void);
extern void func_8003EA3C(Prop *);
extern void func_800693B8(Prop *);
extern void func_80022F2C(void);
extern void func_8003BD40(Light *, int, int, int);
extern void func_8003BD50(Light *, int);
extern void func_8003BB78(Light *, int);
extern void func_8003BC68(int);
extern void func_8006A11C(Matrix *, OrderTable *);
extern void func_80039F04(void);
extern void func_8003E650(void);
extern void func_80065920(OrderTable *);
extern void func_8008A46C(int);

static inline void gte_SetRotMatrix(Matrix *r)
{
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     : : "r"(r) : "$12", "$13", "$14");
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

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

void func_8003E1F4(void)
{
    int count;
    int i;
    Prop *props;
    Prop *prop;
    SkyColors *sky;
    int den;
    int num;
    LevelData *data;

    func_8008DC0C();
    if (D_800D3034.current == D_800D2FE4.last_view - 1) {
        func_8005A8C0();
        func_8006C06C();
        func_8003EB80();
    }
    D_800A5B94 = 768;
    D_800A5B98 = func_8008A438(768);
    D_800A5B9C = D_800A5B98 + 768;
    D_800A5BA0 = func_8008DC84(D_800A5B98 + 768);
    __asm__ volatile("");
    data = D_800D2FE4.data;
    den = data->den;
    num = data->num;
    if (den == 0) {
        den = 2;
    }
    func_8003E9A8(D_800D2FE4.data->den * 4, 4096 - fixed_div(num, den));
    func_8006A0DC();
    props = D_800D2FE4.data->props;
    count = func_800201C0();
    for (i = 0; i < count; i++) {
        func_8003EA3C(&props[D_800D2E00[i]]);
        if (*props[D_800D2E00[i]].model != 0 && props[D_800D2E00[i]].model != 0) {
            func_800693B8(&props[D_800D2E00[i]]);
        }
    }
    func_80022F2C();
    sky = &D_800D2FE4.data->sky;
    func_8003BD40(&D_800DE0EC[0], sky->c[4] << 4, sky->c[5] << 4, sky->c[6] << 4);
    func_8003BD50(&D_800DE0EC[0], ((sky->c[3] << 16) + (sky->c[2] << 8)) | sky->c[1]);
    func_8003BD40(&D_800DE0EC[1], sky->c[10] << 4, sky->c[11] << 4, sky->c[12] << 4);
    func_8003BD50(&D_800DE0EC[1], ((sky->c[9] << 16) + (sky->c[8] << 8)) | sky->c[7]);
    func_8003BB78(D_800DE0EC, 2);
    func_8003BC68(((sky->c[18] << 16) + (sky->c[17] << 8)) | sky->c[16]);
    {
        OrderTable *ot;

        ot = &D_800D5B94[D_800A48B4];
        func_8006A11C(&D_800D3034.views[D_800D3034.current].rot, ot);
    }
    func_80039F04();
    func_8003E650();
    func_8006A0DC();
    {
        register int c asm("$5");

        c = D_800D3034.current;
        gte_SetRotMatrix(&D_800D3034.views[c].rot);
    }
    func_80065920(&D_800D5B94[D_800A48B4]);
    func_8008DC84(D_800A5BA0);
    D_800A5B9C = 0;
    D_800A5BA0 = 0;
    D_800A5B98 = 0;
    func_8008A46C(D_800A5B94);
    D_800A5B94 = 0;
    __asm__ volatile("");
}
