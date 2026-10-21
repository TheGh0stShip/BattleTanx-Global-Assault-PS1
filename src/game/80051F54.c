typedef struct {
    short a0;
    short a2;
    short a4;
    char pad6[2];
    int a8;
    int aC;
    int a10;
    char pad14[0x20 - 0x14];
    unsigned char id;
    unsigned char a21;
    char pad22[2];
} Team;
typedef struct {
    char pad0[0x12];
    unsigned char kind[4];
    char pad16[2];
    int value[4];
    int pair[4][2];
    char pad48[0x5C - 0x48];
    int locked;
} Info;
typedef struct {
    char *models;
    int mode;
    unsigned char humans;
    unsigned char count;
    char padA;
    unsigned char team[46];
    unsigned char type[7];
    Info *info;
} Setup;
typedef struct {
    unsigned char flags;
    unsigned char index;
    char pad2[2];
    Team *team;
    int a8;
    int aC;
    int value;
    int stats[7];
    char *model;
    unsigned char kind;
    char pad35[3];
    int mode;
    int a3C;
    int pair[2];
} Desc;
typedef struct {
    char data[0x114];
} Player;
extern Player D_800E3E68[];
extern Team D_800E3DB4[];
extern unsigned char D_800AED4C;
typedef struct {
    int pad0;
    int start;
    int values[4];
} StartInfo;
extern StartInfo D_800E53FC;
extern Setup D_800D2FE4;
extern unsigned int D_800A6074;
extern int D_800B01E4[];
extern int D_800B0200[];
extern int D_800B021C[];
extern int D_800B0238[];
extern int D_800B0254[];
extern int D_800B0270[];
extern int D_800A5B74;
extern int D_800EB1A8;
extern char D_800BF894[];
extern void func_8008AA48(void *, int, int);
extern void func_8008A7BC(void *, void *, int);
extern int func_80022920(void);
extern void func_800516B8(Player *, Desc *);
extern void func_80053268(void);
extern void func_80076A90(void *, int, void *, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
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
    unsigned int dv;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    __asm__("" : : "r"(denominator));
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

static inline void team_reset(Team *team, int id) {
    team->a0 = 0;
    team->a2 = 0;
    team->a4 = 0;
    team->a8 = 0;
    team->aC = 0;
    team->a10 = 0;
    team->id = id;
    team->a21 = 0;
}

void func_80051F54(void) {
    Desc desc;
    int i;
    int j;
    int scale;
    int value;
    int flags;

    func_8008AA48(D_800E3E68, 0, 0x564);
    func_8008AA48(D_800E3DB4, 0, 0xB4);
    if (D_800AED4C & 1) {
        D_800E53FC.start = 700;
    }
    D_800E3DB4[0].a0 = 0;
    D_800E3DB4[0].a2 = 0;
    D_800E3DB4[0].a4 = 0;
    D_800E3DB4[0].a8 = 0;
    D_800E3DB4[0].id = 0;
    D_800E3DB4[0].a21 = 0;
    team_reset(&D_800E3DB4[1], 1);
    team_reset(&D_800E3DB4[2], 2);
    team_reset(&D_800E3DB4[3], 3);
    D_800E3DB4[0].aC = D_800E53FC.start;
    D_800E3DB4[0].a10 = D_800E53FC.start;
    for (i = 0; i < D_800D2FE4.count; i++) {
        desc.flags = 0;
        if (i < D_800D2FE4.humans) {
            flags = 2;
            desc.flags = flags;
            desc.aC = desc.a8 = D_800E53FC.values[i];
            if (D_800D2FE4.info->locked != 0) {
                desc.flags = 10;
            }
        }
        desc.model = D_800D2FE4.models + (D_800D2FE4.type[i] * 60 + 36);
        desc.index = i;
        desc.team = &D_800E3DB4[D_800D2FE4.team[i]];
        desc.value = D_800D2FE4.info->value[D_800D2FE4.type[i]];
        desc.a3C = 0;
        if (desc.flags & 2) {
            switch (D_800A6074) {
            case 1:
                func_8008A7BC(desc.stats, D_800B0238, 28);
                break;
            case 2:
                func_8008A7BC(desc.stats, D_800B0254, 28);
                break;
            case 3:
                func_8008A7BC(desc.stats, D_800B0270, 28);
                break;
            }
            for (j = 0; j < 7; j++) {
                desc.stats[j] = fixed_mul(func_80022920(), desc.stats[j]);
            }
            desc.pair[1] = 0;
            desc.pair[0] = 0;
        } else {
            switch (D_800A6074) {
            case 1:
                func_8008A7BC(desc.stats, D_800B01E4, 28);
                break;
            case 2:
                func_8008A7BC(desc.stats, D_800B0200, 28);
                break;
            case 3:
                func_8008A7BC(desc.stats, D_800B021C, 28);
                break;
            }
            for (j = 0; j < 7; j++) {
                scale = func_80022920();
                value = desc.stats[j];
                if (scale == 0) {
                    scale = 2;
                }
                desc.stats[j] = fixed_div(value, scale);
            }
            func_8008A7BC(desc.pair, D_800D2FE4.info->pair[D_800D2FE4.type[i]], 8);
        }
        desc.kind = D_800D2FE4.info->kind[D_800D2FE4.type[i]];
        if (desc.flags & 2) {
            if (D_800D2FE4.mode == 11) {
                desc.mode = 4;
            } else {
                desc.mode = 3;
            }
        } else {
            if (D_800D2FE4.mode == 11) {
                desc.mode = 1;
            } else {
                desc.mode = 8;
            }
        }
        func_800516B8(&D_800E3E68[i], &desc);
    }
    func_80053268();
    if (D_800A5B74 == 0) {
        D_800A5B74 = 1;
        func_80076A90(&D_800E3DB4[0].aC, 4, D_800BF894, 1, D_800EB1A8);
    }
}
