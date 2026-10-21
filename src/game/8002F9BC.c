int abs(int);

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


static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    unsigned int n;
    int d;
    unsigned int m;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int div;
    int result;

    d = abs(denominator);
    __asm__("" : "+r"(d));
    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        m = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                div = d >> scale;
            } else {
                div = d << -scale;
            }
            quotient = m / div;
            quotient <<= n_zeros;
        } else {
            quotient = m / (d >> -excess);
        }
    } else {
        m = n << 12;
        quotient = m / denominator;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}


extern int D_800DE30C;
int func_8008ABF0(int);

static inline int ramp(int dist, int scale) {
    int speed;
    int root;

    speed = fixed_mul(D_800DE30C, scale);
    if (dist < 4096) {
        root = 4096;
    } else {
        root = func_8008ABF0(dist);
    }
    return fixed_div(fixed_mul(root, speed), 0x2CB89);
}

static inline int ramp_end(int length, int pos, int scale) {
    int speed;
    int root;
    int dist;

    speed = fixed_mul(D_800DE30C, scale);
    dist = length - pos;
    if (dist < 4096) {
        root = 4096;
    } else {
        root = func_8008ABF0(dist);
    }
    return fixed_div(fixed_mul(root, speed), 0x2CB89);
}

int func_8002F9BC(int length, int pos, int scale, unsigned char mode, unsigned char phase) {
    switch (mode) {
    case 1:
        return fixed_mul(D_800DE30C, scale);
    case 0:
        switch (phase) {
        case 0:
            if (pos < 0xBB8000) {
                return ramp(pos, scale);
            }
            if (pos > length - 0xBB8000) {
                return ramp_end(length, pos, scale);
            }
            return fixed_mul(D_800DE30C, scale);
        case 1:
            if (pos < 0xBB8000) {
                return -ramp(pos, scale);
            }
            if (pos > length - 0xBB8000) {
                return -ramp_end(length, pos, scale);
            }
            return -fixed_mul(D_800DE30C, scale);
        }
        break;
    }
    return 0;
}
