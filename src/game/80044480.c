typedef struct Tank {
    char pad0[0x8];
    int x;
    char pad1[0x10 - 0xC];
    int z;
    char pad2[0x2C - 0x14];
    unsigned short heading;
    char pad3[0x34 - 0x2E];
    int body[2];
    int speed_limit;
    int speed;
    char pad4[0x6E - 0x44];
    unsigned short yaw;
    char pad5[0x90 - 0x70];
    unsigned char input_flags;
    char pad6[0x9C - 0x91];
    int kind;
    char pad7[0x27E - 0xA0];
    unsigned short swing;
    int swing_offset[3];
    int swing_state;
} Tank;

extern int D_800DE30C;

int abs(int);
void func_8001F094(void *, int, int);

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

static inline int sine_lookup(int angle) {
    register int mask asm("$8");
    register int index asm("$9");
    int value;

    __asm__ volatile("" : : "r"(angle));
    mask = angle & 0x4000;
    index = angle & 0x3FFF;
    __asm__ volatile("");
    if (mask != 0) {
        __asm__ volatile("");
        mask = 0x3FFF;
        __asm__ volatile("sub %0,%1,%0" : "=r"(index) : "r"(mask), "0"(index));
    }
    index &= 0x3FFE;
    __asm__ volatile(".set noat\n\tlui $1,0x800b\n\taddu $1,$1,%0\n\tlhu %0,3820($1)\n\t.set at" : "=r"(index) : "0"(index));
    mask = angle & 0x8000;
    if (mask != 0) {
        __asm__ volatile("neg %0,%0" : "=r"(index) : "0"(index));
    }
    __asm__ volatile("");
    value = index << 1;
    __asm__ volatile("" : : "r"(index));
    return value;
}

static inline int cosine_lookup(int angle) {
    register int mask asm("$8");
    register int index asm("$9");
    register int next asm("$10");
    int value;

    __asm__ volatile("" : : "r"(angle));
    next = angle + 0x4000;
    __asm__ volatile("" : : "r"(angle));
    mask = next & 0x4000;
    index = next & 0x3FFF;
    __asm__ volatile("beqz %1,1f\n\tnop\n\tli %1,16383\n\tsub %0,%1,%0\n1:\n\tandi %0,%0,0x3ffe\n\t.set noat\n\tlui $1,0x800b\n\taddu $1,$1,%0\n\tlhu %0,3820($1)\n\t.set at\n\tandi %1,%2,0x8000\n\tbeqz %1,2f\n\tnop\n\tneg %0,%0\n2:"
                     : "=r"(index), "=r"(mask)
                     : "r"(next), "0"(index), "1"(mask));
    value = index << 1;
    __asm__ volatile("" : : "r"(index));
    return value;
}

static inline int cosine_lookup_u16(unsigned short angle) {
    register int mask asm("$8");
    register int index asm("$9");
    register int next asm("$10");
    int value;

    __asm__ volatile("addu %0,%1,0x4000" : "=r"(next) : "r"(angle));
    mask = next & 0x4000;
    index = next & 0x3FFF;
    __asm__ volatile("beqz %1,1f\n\tnop\n\tli %1,16383\n\tsub %0,%1,%0\n1:\n\tandi %0,%0,0x3ffe\n\t.set noat\n\tlui $1,0x800b\n\taddu $1,$1,%0\n\tlhu %0,3820($1)\n\t.set at\n\tandi %1,%2,0x8000\n\tbeqz %1,2f\n\tnop\n\tneg %0,%0\n2:"
                     : "=r"(index), "=r"(mask)
                     : "r"(next), "0"(index), "1"(mask));
    value = index << 1;
    __asm__ volatile("" : : "r"(index));
    return value;
}

static inline int sine_lookup_u16(unsigned short angle) {
    register int mask asm("$8");
    register int index asm("$9");
    int value;

    __asm__ volatile("andi %1,%2,0x4000\n\tandi %0,%2,0x3fff\n\tbeqz %1,1f\n\tnop\n\tli %1,16383\n\tsub %0,%1,%0\n1:\n\tandi %0,%0,0x3ffe\n\t.set noat\n\tlui $1,0x800b\n\taddu $1,$1,%0\n\tlhu %0,3820($1)\n\t.set at\n\tandi %1,%2,0x8000\n\tbeqz %1,2f\n\tnop\n\tneg %0,%0\n2:"
                     : "=r"(index), "=r"(mask)
                     : "r"(angle));
    value = index << 1;
    __asm__ volatile("" : : "r"(index));
    return value;
}

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
    unsigned int dv;
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
                dv = d >> scale;
            } else {
                dv = d << -scale;
            }
            quotient = (unsigned int)n / dv;
            quotient <<= n_zeros;
        } else {
            dv = d >> -excess;
            quotient = (unsigned int)n / dv;
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

static inline void swing_offset_update(int *offset, unsigned short swing) {
    int angle = swing;

    offset[0] = fixed_mul(sine_lookup(angle) >> 4, 0x61B33);
    offset[1] = 0x61B33 - fixed_mul(cosine_lookup(angle) >> 4, 0x61B33);
    offset[2] = 0;
}

void func_80044480(Tank *t, short turn) {
    unsigned short swing;
    unsigned short next;
    unsigned int bits;
    unsigned int frac;
    int step;
    int heading;
    int limit;
    short sign;
    int num;
    int den;

    switch (t->kind) {
    case 3:
        if (t->swing_state == 1) {
            t->swing_state = 0;
        }
        if (t->input_flags & 0xF) {
            if (turn < 0) {
                t->swing_state = 2;
                t->swing--;
            } else if (turn > 0) {
                t->swing_state = 3;
            }
        }
        switch (t->swing_state) {
        case 3: {
            unsigned short rate;
            int k;
            rate = fixed_mul(D_800DE30C, 1820);
            if ((t->swing & 0x7FFF) < 0x2000) {
                rate = fixed_mul(10240, rate & 0xFFFF);
            }
            next = t->swing + rate;
            bits = next;
            if ((bits >> 15) != (t->swing >> 15)) {
                t->swing = next - (bits & 0x7FFF);
                t->swing_state = 1;
                t->swing += 0x8000;
            } else {
                t->swing = next;
            }
            swing_offset_update(t->swing_offset, t->swing);
            k = fixed_mul(0x32000, rate & 0xFFFF);
            __asm__("" : : "r"(k));
            __asm__("" : : "r"(k));
            t->x += fixed_mul(k, -(cosine_lookup_u16(t->heading) >> 4));
            k = fixed_mul(k, sine_lookup_u16(t->heading) >> 4);
            t->z += k;
            break;
        }
        case 2: {
            unsigned short rate;
            int k;
            rate = fixed_mul(D_800DE30C, 1820);
            swing = t->swing;
            frac = swing & 0x7FFF;
            if (frac > 0x6000) {
                rate = fixed_mul(10240, rate & 0xFFFF);
            }
            next = swing - rate;
            if ((next >> 15) != (swing >> 15)) {
                t->swing = swing - frac;
                t->swing_state = 1;
                t->swing += 0x8000;
            } else {
                t->swing = next;
            }
            __asm__("" : : "r"(rate));
            __asm__("" : : "r"(rate));
            __asm__("" : : "r"(rate));
            swing_offset_update(t->swing_offset, t->swing);
            k = fixed_mul(0x32000, rate & 0xFFFF);
            __asm__("" : : "r"(k));
            __asm__("" : : "r"(k));
            t->x -= fixed_mul(k, -(cosine_lookup_u16(t->heading) >> 4));
            k = fixed_mul(k, sine_lookup_u16(t->heading) >> 4);
            t->z -= k;
            break;
        }
        }
        break;
    case 4:
        if (turn != 0) {
            limit = fixed_mul(2867, t->speed);
            heading = t->heading;
            if (turn < 0) {
                heading += 0x4000;
                sign = 1;
            } else {
                heading -= 0x4000;
                sign = -1;
            }
            func_8001F094(t->body, D_800DE30C * 1500, heading & 0xFFFF);
            if (limit < t->speed_limit) {
                t->speed_limit = limit;
            }
            num = t->speed_limit;
            den = limit;
            if (den == 0) {
                den = 2;
            }
            step = fixed_mul(fixed_div(num, den), 4096);
            if (sign > 0) {
                t->yaw -= step;
            } else {
                t->yaw += step;
            }
        }
        break;
    }
}
