typedef struct {
    char pad0[4];
    short x;
    short y;
} Target;
typedef struct {
    unsigned short type;
    short pad2;
    int value;
    Target *data;
} Widget;
typedef struct {
    char pad0[2];
    short x;
    short y;
    char pad6[0x10 - 6];
    Widget *widget;
} Item;

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


extern int abs(int);

static inline int abs_max(int a, int b) {
    int r = abs(a);

    b = abs(b);
    if (r < b) {
        r = b;
    }
    return r;
}

static inline int fixed_to_int(int value) {
    int r;
    int t = value;

    if (t >= 0) {
        r = t >> 12;
    } else {
        r = -(-t >> 12);
    }
    return r;
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int shifted;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    n = numerator;
    if (n < 0) {
        n = -n;
    }
    d = abs(denominator);
    __asm__("" : : "r"(negative), "r"(denominator));
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        shifted = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)shifted / (d >> scale);
            } else {
                quotient = (unsigned int)shifted / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)shifted / (d >> -excess);
        }
    } else {
        shifted = n << 12;
        quotient = (unsigned int)shifted / d;
    }
    n_zeros = quotient;
    if (negative) {
        n_zeros = -n_zeros;
    }
    return n_zeros;
}

int func_80058B9C(Item *item) {
    Widget *w = item->widget;
    Target *t = w->data;
    int old = w->value;
    int frac;

    w->value = old - 4096;
    if (w->value <= 0) {
        switch (w->type) {
        case 3:
            item->x = t->x;
            break;
        case 4:
            item->y = t->y;
            break;
        case 2:
        default:
            item->x = t->x;
            item->y = t->y;
            break;
        }
        return 1;
    }
    if (old == 0) {
        old = 2;
    }
    frac = fixed_div(4096, old);
    switch (w->type) {
    case 3:
        item->x += fixed_to_int(frac * (t->x - item->x));
        break;
    case 4:
        item->y += fixed_to_int(frac * (t->y - item->y));
        break;
    case 2:
    default:
        item->x += fixed_to_int(frac * (t->x - item->x));
        item->y += fixed_to_int(frac * (t->y - item->y));
        break;
    }
    return 0;
}
