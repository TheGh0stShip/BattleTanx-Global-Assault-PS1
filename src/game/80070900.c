typedef struct { int time; int x; int y; unsigned char r, g, b, pad; } Key;
typedef struct { char pad0[24]; int time; int x; int y; unsigned char r, g, b, pad27; int key; } Path;
typedef struct { int pad0; int x; int y; char pad12[437]; unsigned char r, g, b; } Cam;
extern Key D_800AE144[];
typedef struct { Cam *cam; } Globals;
extern Globals D_800D2FE4;
int abs(int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30" : : "r"(value));
}

static inline void gte_nop(void) {
    __asm__ volatile("nop");
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_nop();
    gte_nop();
    gte_stlzc(&count);
    return count;
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        quotient = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = quotient / (d >> scale);
            } else {
                quotient = quotient / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = quotient / (d >> -excess);
        }
    } else {
        quotient = n << 12;
        quotient = quotient / d;
    }
    if (negative) {
        return -quotient;
    }
    return quotient;
}

static inline int pick_int(int v, int *fallback)
{
    if (v == -1) {
        v = *fallback;
    }
    return v;
}

static inline int pick_colour(int v, unsigned char *fallback)
{
    int c = (short)v;
    if (v == 255) {
        c = *fallback;
    }
    return c;
}

int func_80070900(Path *p)
{
    int time = p->time;
    int span, f;
    int x0, y0, x1, y1;
    int r0, g0, b0, r1, g1, b1;

    while (time >= D_800AE144[p->key + 1].time) {
        p->key++;
        if (p->key >= 3) {
            D_800D2FE4.cam->r = p->r;
            D_800D2FE4.cam->g = p->g;
            D_800D2FE4.cam->b = p->b;
            return 1;
        }
    }
    {
        int k = p->key;
        int start = D_800AE144[k].time;
        int end = D_800AE144[k + 1].time;
        int dt;
        span = end - start;
        dt = p->time - start;
        if (span == 0) {
            span = 2;
        }
        f = fixed_div(dt, span);
    }

    x0 = pick_int(D_800AE144[p->key].x, &p->x);
    y0 = pick_int(D_800AE144[p->key].y, &p->y);
    x1 = pick_int(D_800AE144[p->key + 1].x, &p->x);
    y1 = pick_int(D_800AE144[p->key + 1].y, &p->y);
    D_800D2FE4.cam->x = x0 + fixed_mul(x1 - x0, f);
    D_800D2FE4.cam->y = y0 + fixed_mul(y1 - y0, f);

    r0 = pick_colour(D_800AE144[p->key].r, &p->r);
    g0 = pick_colour(D_800AE144[p->key].g, &p->g);
    b0 = pick_colour(D_800AE144[p->key].b, &p->b);
    r1 = pick_colour(D_800AE144[p->key + 1].r, &p->r);
    g1 = pick_colour(D_800AE144[p->key + 1].g, &p->g);
    b1 = pick_colour(D_800AE144[p->key + 1].b, &p->b);
    D_800D2FE4.cam->r = r0 + fixed_mul(r1 - r0, f);
    D_800D2FE4.cam->g = g0 + fixed_mul(g1 - g0, f);
    D_800D2FE4.cam->b = b0 + fixed_mul(b1 - b0, f);
    return 0;
}
