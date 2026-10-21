typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Link {
    char pad00[0x1C];
    struct Link *next;
} Link;

typedef struct Body {
    char pad00[0xA4];
    Link *attached;
} Body;

typedef struct Driver {
    char pad00[4];
    short kind;
    char pad06[2];
    Body *body;
} Driver;

typedef struct Ammo {
    unsigned short primary;
    char pad02[2];
    unsigned short secondary;
} Ammo;

typedef struct Waypoint {
    char pad00[0xC];
    Ammo *ammo;
    char pad10[0x60 - 0x10];
    Driver *driver;
    char pad64[0x114 - 0x64];
} Waypoint;

typedef struct Seat {
    char pad00[2];
    short owner;
    char pad04[4];
    unsigned char *info;
    char pad0C[0x40 - 0xC];
} Seat;

typedef struct GameState {
    int pad00;
    int mode;
    unsigned char players;
    char pad09[7];
    int base;
} GameState;

extern GameState D_800D2FE4;
extern int D_800C60D0;
extern unsigned short D_800D3170;
extern short D_800D326C;
extern Seat *D_800D3258;
extern void *D_800AAF34;
extern int D_800E4864;
extern int D_800AAF38;
extern int D_800AAF3C;
extern int D_800AAF40;
extern Color D_800AAF44;
extern Color D_800AAF48;
extern int D_800E4AC4;
extern int D_800E4AC8;
extern Waypoint D_800E3E68[];
extern void func_80056160(void *, short, short, int, int, Color *);

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline Waypoint *waypoint_of(short index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800633C0(void) {
    short ys[2];
    int skip;
    short split;
    short right;
    short left;
    short i;
    short j;
    short step;
    short y;
    short x;
    int count;
    int scale;

    skip = 9;
    scale = 2867;
    left = 15;
    right = 470;
    if (D_800C60D0 == 8 && D_800D3170 != 0) {
        return;
    }
    if (D_800D326C != -1) {
        Seat *seat;

        if (D_800D2FE4.players == 1) {
            return;
        }
        seat = (Seat *)((D_800D326C << 6) + (int)D_800D3258);
        if (seat->owner != -1) {
            return;
        }
        skip = seat->info[7];
    }
    if (D_800AAF34 == 0) {
        D_800AAF34 = &D_800E4864;
    }
    if (D_800D2FE4.players == 1) {
        ys[0] = 20;
    } else {
        left = 150;
        ys[0] = 103;
        right = 385;
        ys[1] = 220;
    }
    split = D_800D2FE4.players - 1;
    if (split != 0 && D_800E3E68[0].ammo != D_800E3E68[1].ammo) {
        split = 0;
    }
    for (i = 0; i < D_800D2FE4.players; i++) {
        if (i == skip) {
            continue;
        }
        if (D_800AAF38 != 0) {
            switch ((unsigned int)D_800D2FE4.mode) {
            case 1:
            case 2:
            case 3:
            case 11:
            case 13:
                D_800E4AC8 = waypoint(i)->ammo->secondary;
                break;
            case 0:
            case 6:
                D_800E4AC8 = waypoint(i)->ammo->primary;
                break;
            case 14:
                D_800E4AC8 = D_800AAF40;
                break;
            case 12:
                D_800E4AC8 = D_800AAF38 - D_800D2FE4.base;
                break;
            default:
                D_800E4AC8 = 0;
                break;
            }
        }
        if (D_800AAF3C != 0) {
            switch ((unsigned int)D_800D2FE4.mode) {
            case 1:
            case 3:
            case 11:
            case 14:
                count = 0;
                if (waypoint(i)->driver->kind == 4) {
                    Link *link;

                    for (link = waypoint_of(i)->driver->body->attached; link != 0; link = link->next) {
                        count++;
                    }
                    D_800E4AC4 = count;
                } else {
                    D_800E4AC4 = 0;
                }
                break;
            default:
                D_800E4AC4 = 0;
                break;
            }
        }
        if (D_800AAF38 != 0 && (split == 0 || D_800D2FE4.players < skip)) {
            if (D_800AAF38 >= 6) {
                step = 170 / D_800AAF38;
            } else {
                step = 25;
            }
            if (split != 0) {
                y = 115;
            } else {
                y = ys[i];
            }
            for (j = 0; j < D_800AAF38; j++) {
                x = left + j * step;
                if (j >= D_800E4AC8) {
                    func_80056160(D_800AAF34, x, y, 2867, scale, &D_800AAF48);
                } else {
                    func_80056160(D_800AAF34, x, y, 2867, scale, &D_800AAF44);
                }
                if (D_800E4AC8 != 0) {
                    func_80056160(D_800AAF34, left + (D_800E4AC8 - 1) * step, y, 2867, scale,
                                  &D_800AAF44);
                }
            }
        }
        if (D_800AAF3C != 0) {
            step = 25;
            if (D_800AAF3C >= 6) {
                step = 170 / D_800AAF3C;
            }
            y = ys[i];
            for (j = 0; j < D_800E4AC4; j++) {
                func_80056160(D_800AAF34, right - j * step, y, 2867, scale, &D_800AAF44);
            }
        }
    }
}
