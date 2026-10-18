typedef struct Waypoint {
    char pad000[6];
    unsigned char flags;
    char pad007[0x114 - 7];
} Waypoint;
extern Waypoint D_800E3E68[];
extern int D_800A6070;
extern int D_800C60D0;
extern int D_800C60DC;
extern unsigned char D_800D3030;
extern unsigned char D_800ABA5A;
extern int func_8007906C(int, unsigned char, int *, int *, int *);
extern void func_80051568(Waypoint *);
extern void func_80061538(void);
extern void func_80054C08(void);
extern void func_8006AF94(int);

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800524D4(int index) {
    Waypoint *wp = waypoint(index);
    int pressed;
    int held;
    int released;

    if (!(wp->flags & 2)) {
        return;
    }
    if (D_800A6070 == 10) {
        return;
    }
    func_8007906C(11, index, &pressed, &held, &released);
    if (pressed != 0 && D_800C60D0 != 7) {
        func_80051568(wp);
    }
    if (func_8007906C(18, index, &pressed, &held, &released) == 0) {
        return;
    }
    if (D_800C60DC == 7) {
        return;
    }
    if (D_800A6070 == 10) {
        return;
    }
    if (D_800D3030 != 0) {
        return;
    }
    D_800ABA5A = index;
    func_80061538();
    D_800C60DC = 7;
    func_80054C08();
    func_8006AF94(0);
}
