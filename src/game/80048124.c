typedef struct TankZone {
    char pad00[0x4];
    short x0;
    short x1;
    short y0;
    short y1;
    char pad0C[0xA8 - 0xC];
    unsigned short radius;
    short inner;
    char padAC[0xD0 - 0xAC];
} TankZone;

typedef struct Squadron {
    char data[0x598];
} Squadron;

extern TankZone D_800A4EF4[];
extern Squadron D_800DE33C[];

void func_80048EDC(void);
void func_800498F4(void);
void func_8004E2AC(Squadron *, int);
int func_8008ABF0(int);

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

static inline int abs_max(int a, int b) {
    int r = abs(a);

    b = abs(b);
    if (r < b) {
        r = b;
    }
    return r;
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
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
    __asm__("" : "+r"(numerator) : "r"(negative));
    numerator = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(numerator);
    excess = n_zeros - 12;
    if (excess < 0) {
        numerator <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)numerator / (d >> scale);
            } else {
                quotient = (unsigned int)numerator / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)numerator / (d >> -excess);
        }
    } else {
        numerator <<= 12;
        quotient = (unsigned int)numerator / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

void func_80048124(void) {
    unsigned short squad;
    unsigned short i;
    TankZone *zone;
    int width;
    int depth;
    int unit;

    func_80048EDC();
    func_800498F4();
    for (squad = 0; squad < 16; squad++) {
        func_8004E2AC(&D_800DE33C[squad], 29);
    }
    for (i = 0; i < 15; i++) {
        unit = 5792;
        zone = &D_800A4EF4[i];
        width = abs_max(zone->x0, zone->x1);
        depth = abs_max(zone->y0, zone->y1);
        zone->radius = fixed_to_int(func_8008ABF0((width * width + depth * depth) << 12));
        {
            int inner_width = abs_max(zone->x0, zone->x1);
            int inner_depth = abs(zone->y0);
            int other = abs(zone->y1);

            if (inner_depth < other) {
                inner_depth = other;
            }
            if (inner_width < inner_depth) {
                inner_depth = inner_width;
            }
            zone->inner = fixed_to_int(fixed_div(inner_depth << 12, unit));
        }
    }
}
