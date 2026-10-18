typedef struct {
    char pad0[8];
    short x;
} Knob;
typedef struct {
    unsigned char tint;
    char pad1;
    short x;
    char pad4[4];
    void *data;
    char padC[0x20 - 0xC];
} Item;
typedef struct {
    char pad0[0x14];
    int left;
    int right;
} Keys;
typedef struct {
    char pad0[4];
    Item *items;
    char pad8[4];
    Keys *keys;
    char pad10[4];
    unsigned short player;
} Menu;
typedef struct {
    char pad0[4];
    unsigned short held;
    char pad6[0x8C - 6];
} Pad;
extern Pad D_800EE028[];
extern char D_800EAD48[];
extern char D_800EAD28[];
extern short D_800E4828;
extern signed char D_800A6080;
extern signed char D_800A6081;
extern unsigned char D_800AACE3;
extern short D_800E4654;
extern short D_800E540C;
extern Item *func_8005A2A0(Menu *);
extern int func_80054A30(unsigned char);
extern void func_80054DC4(int);
extern void func_8006AC7C(int);
extern void func_8006B044(short);
extern void func_80091A90(short, short);
extern void func_8006AFFC(int);

static inline short direction(Menu *menu) {
    unsigned short held = D_800EE028[menu->player].held;

    if (held & menu->keys->right) {
        return 2;
    }
    if (held & menu->keys->left) {
        return -2;
    }
    return 0;
}

static inline void set_bar(Item *bar, int v) {
    ((Knob *)bar->data)->x = v + 5;
    bar[1].x = v + 28;
    bar[2].x = v + 32;
}

int func_8005B360(Menu *menu) {
    Item *item = func_8005A2A0(menu);
    short dir;
    int music;
    int sfx;

    if (item->data == D_800EAD48) {
        dir = direction(menu);
        if (dir != 0) {
            if (--D_800E4828 < 0) {
                func_80054A30(3);
                D_800E4828 += 5;
            }
            D_800A6080 += dir;
            if (D_800A6080 >= 92) {
                D_800A6080 = 91;
            } else if (D_800A6080 < 0) {
                D_800A6080 = 0;
            }
            func_80054DC4(D_800A6080 * 60);
        }
        item[2].tint = dir > 0 ? 16 : 1;
    }
    if (item->data == D_800EAD28) {
        if (D_800AACE3 != 0) {
            func_8006AC7C(1);
            D_800AACE3 = 0;
        }
        dir = direction(menu);
        if (dir != 0) {
            D_800A6081 += dir;
            if (D_800A6081 >= 92) {
                D_800A6081 = 91;
            } else if (D_800A6081 < 0) {
                D_800A6081 = 0;
            }
            func_8006B044(D_800A6081 * 360);
            func_80091A90(D_800E540C, D_800E540C);
        }
        item[2].tint = dir > 0 ? 16 : 1;
    } else if (D_800AACE3 == 0) {
        D_800AACE3 = 1;
        func_8006AFFC(0);
    }
    music = D_800E4654;
    music /= 60;
    sfx = D_800E540C;
    sfx /= 360;
    set_bar(&menu->items[5], music);
    set_bar(&menu->items[9], sfx);
    return 0;
}
