typedef struct {
    char pad0[0xE074];
    unsigned char enabled;
    char padE075;
    unsigned short blink_color;
    int team;
} System;
typedef struct {
    char pad0[0xC];
    int team;
    char pad10[4];
    unsigned int state;
    char pad18[0x4C - 0x18];
    int timer;
    unsigned short color;
    unsigned char blink;
} Marker;
extern System *D_800A5B24;
extern int D_800D2FE8;
extern int D_800D2FE0;
extern void func_80051340(Marker *, int, int, int);
extern int func_80050B2C(Marker *);
extern void func_80051104(Marker *);

void func_80050CF8(Marker *m) {
    switch (m->state) {
    case 0:
        if (D_800A5B24->enabled == 0) {
            break;
        }
        switch (D_800D2FE8) {
        case 1:
        case 2:
        case 3:
        case 11:
            func_80051340(m, 2, 0, 0);
            break;
        case 4:
        case 10:
            if (D_800A5B24->team != m->team) {
                func_80051340(m, 7, 0, 0);
                break;
            }
        case 12:
        case 13:
        case 14:
        default:
            func_80051340(m, 1, 0, 0);
            break;
        case 9:
            break;
        }
        break;
    case 1:
        break;
    case 2:
    case 6:
        func_80050B2C(m);
        break;
    case 3:
    case 4:
    case 5:
        if (func_80050B2C(m) == 0) {
            func_80051104(m);
        }
        break;
    case 7:
        if (m->timer <= D_800D2FE0) {
            m->blink = m->blink == 0;
            m->timer = D_800D2FE0 + 150;
            if (m->blink != 0) {
                m->color = D_800A5B24->blink_color;
            }
        }
        if (D_800D2FE8 != 10) {
            func_80051104(m);
        }
        break;
    }
}
