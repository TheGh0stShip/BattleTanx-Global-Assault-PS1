typedef struct {
    char pad0[0xC];
    int team;
    char pad10[0x94 - 0x10];
    int armor;
    char pad98[0x114 - 0x98];
} Waypoint;

typedef struct {
    char pad0[0x50];
    int score;
} Kind;

typedef struct {
    char pad0[0x1B];
    unsigned char kind;
    char pad1C;
    unsigned char owner;
    char pad1E[0x38 - 0x1E];
    int health;
} Object;

typedef struct {
    char pad0[0xC];
    int team;
} Tank;

extern Waypoint D_800E3E68[];
extern Kind D_800A44D4[];
extern void func_800530E0(Tank *, int, int);

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


int abs(int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
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
    n = abs(numerator);
    d = abs(denominator);
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
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80029308(Object *obj, int damage, Tank *source) {
    Waypoint *w;
    int armor;

    damage <<= 12;
    if (obj->health <= 0) {
        return;
    }
    w = waypoint_get(obj->owner);
    armor = w->armor;
    if (armor == 0) {
        armor = 2;
    }
    obj->health -= fixed_to_int(fixed_div(damage, armor));
    if (obj->health <= 0 && source != 0) {
        w = waypoint_get(obj->owner);
        if (source->team != w->team) {
            func_800530E0(source, D_800A44D4[obj->kind].score, 0);
        }
    }
}
