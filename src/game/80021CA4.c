typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[0xC];
    int f0C;
    char pad10[0x18 - 0x10];
    int f18;
    int f1C;
} Stats;

typedef struct {
    short id;
    short pad02;
    short kind;
    short pad06;
    union {
        unsigned short angle;
        struct Unit *unit;
        Vector pos;
    } u;
    char pad14[0x28 - 0x14];
    unsigned short f28;
} Node;

typedef struct Unit {
    char pad0[8];
    Vector pos;
    char pad14[0x2C - 0x14];
    unsigned short f2C;
    unsigned short pad2E;
    unsigned short f30;
    char pad32[0x594 - 0x32];
    int stamp;
} Unit;

typedef struct {
    char pad0[0x48];
    Node *focus;
    short focus_id;
} Player;

typedef struct {
    char pad0[0xC];
    Stats *stats;
    char pad10[0x58 - 0x10];
    int ready;
    Player *player;
    char pad60[0x70 - 0x60];
    int f70;
    short f74;
    char pad76[0xD0 - 0x76];
    unsigned short fD0;
    char padD2[0x114 - 0xD2];
} Waypoint;

typedef struct {
    char pad0[0x24];
    int x;
    int z;
    unsigned short f2C;
    char pad2E[0x3C - 0x2E];
} Spot;

typedef struct {
    Spot *spots;
    int type;
    unsigned char count;
    unsigned char count2;
    char pad0A[0x44 - 0x0A];
    int f44;
} Setup;

typedef struct {
    unsigned char active;
    unsigned char index;
} ViewSlot;

typedef struct {
    char pad0[0x9C];
} View;

extern Setup D_800D2FE4;
extern Waypoint D_800E3E68[];
extern ViewSlot D_800D3034;
extern View D_800D3038[];
extern unsigned char D_800D3030;
extern int D_800C60CC;
extern int D_800C60C8;
extern int D_800C60C4;
extern int D_800C60E4;
extern unsigned int D_800C60D0;
extern int D_800C60D4;
extern int D_800C60D8;
extern int D_800C60DC;
extern int D_800C60E8;
extern int D_800D2FE0;
extern int D_800DE30C;
extern unsigned short D_800D3170;
extern int D_800A4384;
extern unsigned char D_800A4354;
extern unsigned char D_800A4380;
extern signed char D_800A606C;
extern int D_80086058;

extern void func_80084898(int);
extern int func_80083A5C(int);
extern void func_80061448(void);
extern int *func_8006A7FC(void);
extern int func_80022ABC(int);
extern int func_80022ADC(void);
extern void func_80063E3C(int, int, int);
extern void func_80068700(void);
extern void func_800524D4(int);
extern void func_80022D64(int);
extern int func_80020F28(void);
extern void func_800323C0(void);
extern void func_800219AC(void);
extern void func_80021B98(void);
extern void func_80054D4C(void);
extern int func_80052E64(Waypoint *);
extern void func_8006AE50(int, int, int);
extern int func_8006A820(void);
extern void func_800530E0(Waypoint *, int, int);
extern int func_80022A08(int);
extern void func_80064FE0(int, int, int, int, int, int, int, int);
extern void func_80065150(int, int, int, int, int, int, int, int, int, int, int);
extern void func_800650DC(int, int, int, int, int, int, int, int);
extern void func_80065280(int, int, int, int, int, int, int, int, int, int, int);
extern void func_8006488C(void);
extern void func_8006F21C(void);
extern void func_80041210(Unit *, Vector *);
extern void func_80014E2C(View *, Vector *, int);
extern void func_8003A610(void);
extern void func_80079CE4(int);
extern void func_8003BB78(int, int);
extern void func_8003E1F4(void);
extern void func_8003A744(void);
extern void func_8003A8F4(void);
extern void func_80076524(void);
extern void func_800201F8(int);

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
    unsigned int n;
    register int d asm("$7");
    register int divisor asm("$2");
    unsigned int m;
    int n_zeros;
    int d_zeros;
    register int excess asm("$6");
    int scale;
    unsigned int quotient;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    n = abs(numerator);
    d = abs(denominator);
    __asm__ volatile("" : "+r"(d));
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        m = n << n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                divisor = d >> scale;
            } else {
                divisor = d << -scale;
            }
            quotient = m / divisor;
            quotient <<= n_zeros;
        } else {
            scale = -excess;
            divisor = d >> scale;
            quotient = m / divisor;
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

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}


static inline int any_ready(void) {
    int i;

    for (i = 0; i < D_800D2FE4.count; i++) {
        if (waypoint_get(i)->ready == 1) {
            return 1;
        }
    }
    return 0;
}

static inline int is_team_game(void) {
    int result = 0;

    if ((unsigned int)D_800D2FE4.type < 15) {
        result = (unsigned int)D_800D2FE4.type >= 7;
    }
    return result;
}

void func_80021CA4(void) {
    int last;
    int now;
    int i;
    unsigned short n;
    Waypoint *w;
    Waypoint *first;
    Waypoint *second;
    Vector pos;

    func_80084898(1);
    last = func_80083A5C(2);
    while (D_800C60CC == 1) {
        if (D_800C60D8 == 0 && D_800C60D0 == 5) {
            func_80061448();
            if (is_team_game()) {
                if (D_800C60D4 != 7) {
                    func_80063E3C(func_80022ABC(func_8006A7FC()[1]), 0x78000, 0);
                }
            } else if (D_800C60D4 != 7 || D_800A4354 != 0) {
                func_80063E3C(func_80022ADC(), 0x78000, 0);
                D_800A4354 = 0;
            }
        }
        func_80068700();
        switch (D_800C60D0) {
        case 7:
        case 8:
            break;
        default: {
            int k;

            for (k = 0; k < D_800D2FE4.count2; k++) {
                func_800524D4(k);
            }
            func_80022D64(2);
            break;
        }
        }
        switch (D_800C60D0) {
        case 5:
            switch (func_80020F28()) {
            case 0:
                break;
            case 1:
                D_800C60DC = 8;
                func_800323C0();
                break;
            case 2:
                D_800C60DC = 6;
                break;
            }
            break;
        case 6:
            if (D_800C60D8 >= 60) {
                D_800C60DC = 8;
                func_800219AC();
            }
            break;
        case 8: {
            int limit = 10;

            if (is_team_game()) {
                limit = 60;
            }
            if (D_800C60D8 < limit) {
                D_800D3170 = 0;
                if (is_team_game() && D_800A4384 == 0) {
                    func_80021B98();
                    D_800A4384 = 1;
                }
                break;
            }
            D_800A4384 = 0;
            if (D_800D3170 != 0) {
                break;
            }
            func_80054D4C();
            if (is_team_game()) {
                first = &D_800E3E68[0];
                second = &D_800E3E68[1];
                for (i = 0; i < D_800D2FE4.count; i++) {
                    int v;

                    w = waypoint_get(i);
                    w->stats->f0C += func_80052E64(w);
                    w->f74 += func_80052E64(w);
                    v = w->stats->f0C;
                    if (v % 5 != 0) {
                        w->stats->f0C = (v + 5) / 5 * 5;
                    }
                    v = w->f74;
                    if ((short)(v % 5) != 0) {
                        w->f74 = (v + 5) / 5 * 5;
                    }
                }
                if (any_ready()) {
                    func_8006AE50(2, 4, 0);
                    func_800530E0(first, func_8006A820(), 1);
                    if (D_800D2FE4.count == 1) {
                        func_80064FE0(first->stats->f1C, first->stats->f18, first->f70, first->fD0, first->f74,
                                      func_80022A08(D_800D2FE4.f44), D_800D2FE0, (short)first->stats->f0C);
                    } else {
                        func_80065150(first->stats->f1C, first->stats->f18, first->f70, second->f70, first->fD0,
                                      second->fD0, first->f74, second->f74, func_80022A08(D_800D2FE4.f44), D_800D2FE0,
                                      (short)first->stats->f0C);
                    }
                } else {
                    func_8006AE50(2, 3, 0);
                    if (D_800D2FE4.count == 1) {
                        func_800650DC(first->stats->f1C, first->stats->f18, first->f70, first->fD0, first->f74,
                                      func_80022A08(D_800D2FE4.f44), D_800D2FE0, (short)first->stats->f0C);
                    } else {
                        func_80065280(first->stats->f1C, first->stats->f18, first->f70, second->f70, first->fD0,
                                      second->fD0, first->f74, second->f74, func_80022A08(D_800D2FE4.f44), D_800D2FE0,
                                      (short)first->stats->f0C);
                    }
                }
            } else {
                func_8006488C();
            }
            D_800D3170 = 1;
            break;
        }
        case 7:
        case 9:
        case 10:
            break;
        }
        func_8006F21C();
        for (n = 0; n < D_800D2FE4.count; n++) {
            Vector *at = 0;
            int size = 0;
            Player *player;
            Node *focus;

            D_800D3034.active = 1;
            D_800D3034.index = n;
            player = waypoint_get(n)->player;
            focus = player->focus;
            if (focus != 0 && player->focus_id == focus->id) {
                int show = 1;

                switch (focus->kind) {
                case 12:
                    at = &focus->u.pos;
                    size = focus->f28;
                    break;
                case 6: {
                    Spot *spot = &D_800D2FE4.spots[n];

                    pos.x = spot->x;
                    pos.y = 0;
                    pos.z = spot->z;
                    size = spot->f2C;
                    at = &pos;
                    break;
                }
                case 3:
                    pos.x = focus->u.pos.y;
                    pos.y = 0;
                    pos.z = focus->u.pos.z;
                    size = focus->u.angle;
                    at = &pos;
                    break;
                case 4: {
                    Unit *unit = focus->u.unit;

                    if (unit->stamp == D_800D2FE0) {
                        show = 0;
                        break;
                    }
                    func_80041210(unit, &pos);
                    pos.x += unit->pos.x;
                    pos.y += unit->pos.y;
                    pos.z += unit->pos.z;
                    pos.x /= 2;
                    pos.y /= 2;
                    pos.z /= 2;
                    size = unit->f2C + unit->f30;
                    at = &pos;
                    break;
                }
                }
                if (show) {
                    func_80014E2C(&D_800D3038[n], at, size & 0xFFFF);
                }
            } else {
                player->focus = 0;
            }
            func_8003A610();
            func_80079CE4(D_800A4380);
            func_8003BB78(0, 0);
            func_8003E1F4();
            D_800D3034.active = 0;
            func_8003A744();
            func_8003A8F4();
        }
        if (D_800C60CC != D_800C60C8) {
            D_800C60C4 = D_800C60CC;
            D_800C60CC = D_800C60C8;
            D_800C60E4 = 0;
        } else {
            D_800C60E4++;
        }
        if (D_800C60D0 != D_800C60DC) {
            D_800C60D4 = D_800C60D0;
            D_800C60D0 = D_800C60DC;
            D_800C60D8 = 0;
        } else {
            D_800C60D8++;
        }
        if (D_800C60E4 >= 4) {
            D_800D3030 = 0;
        }
        func_80076524();
        if (D_80086058 != 0) {
            __asm__ volatile("break 0x400");
        }
        now = func_80083A5C(2);
        {
            int prev = last;

            last = now;
            D_800C60E8 = now - prev;
        }
        if (D_800C60E8 > 200) {
            D_800C60E8 = 200;
        }
        func_80084898(D_800C60E8);
        func_800201F8(D_800A606C);
        if (D_800C60D0 != 7) {
            D_800D2FE0 += D_800C60E8 >> 4;
        }
        D_800DE30C = fixed_div(D_800C60E8 << 12, 0x21555);
    }
}
