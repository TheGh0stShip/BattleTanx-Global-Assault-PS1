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
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
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
                quotient = m / (d >> scale);
            } else {
                quotient = m / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = m / (d >> -excess);
        }
    } else {
        m = n << 12;
        quotient = m / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}


typedef struct {
    int pad[2];
    int x;
    int pad2;
    int z;
    unsigned short heading;
    signed char hp;
    char pad4[40 - 23];
    int model;
    char pad5[53 - 44];
    unsigned char state;
    char pad6;
    unsigned char team;
} Obj;
typedef struct { int x; int z; int pad[3]; int amount; } Blast;
extern unsigned char D_800D5A88;
extern int D_800D5A80;
int func_8008AE30(int, int);
void func_8002EA70(Obj *);
void func_80035948(int, int *, int, int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_8002F3D8(Obj *obj, void *msg, Blast *b) {
    int dx;
    int dz;
    int dist;
    int range;

    func_8008AE30(obj->x - b->x, obj->z - b->z);
    if (obj->team == 1 && D_800D5A88 == 97) {
        return;
    }
    dx = to_int(obj->x - b->x);
    dz = to_int(obj->z - b->z);
    dist = dx * dx + dz * dz;
    range = D_800D5A80;
    if (dist > range) {
        return;
    }
    switch (obj->state) {
    case 0 ... 3:
        break;
    default:
        return;
    }
    if (b->amount != 250) {
        if (obj->hp < b->amount) {
            obj->hp = 0;
        } else {
            obj->hp -= b->amount;
        }
    } else {
        if (dist < fixed_mul(819, range)) {
            func_8002EA70(obj);
            return;
        }
        if (dist < fixed_mul(1638, range)) {
            func_80035948(obj->model, &obj->x, obj->heading, 0, 0, 0, 0, 0);
            func_8002EA70(obj);
            return;
        }
        if (dist < fixed_mul(2457, range)) {
            if (obj->hp < b->amount) {
                obj->hp = 0;
            } else {
                obj->hp -= b->amount;
            }
            return;
        }
        if (dist < fixed_mul(3276, range)) {
            if (obj->hp < b->amount) {
                obj->hp = 0;
            } else {
                obj->hp -= b->amount;
            }
            return;
        }
        dist = (range - dist) * 5;
        if (range == 0) {
            range = 2;
        }
        obj->hp -= fixed_mul(15, fixed_div(dist, range));
    }
}
