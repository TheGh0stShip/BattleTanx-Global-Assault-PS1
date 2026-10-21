typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[0xC];
    int money;
} Account;

typedef struct {
    char pad0[7];
    unsigned char player;
    char pad8[4];
    Account *account;
    char pad10[0x60 - 0x10];
    void *menu;
    char pad64[0xA4 - 0x64];
    unsigned char color;
} Owner;

typedef struct {
    char pad0[8];
    Owner *owner;
    int count;
    int cursor;
    unsigned int state;
    int timer;
} Menu;

typedef struct {
    int texture;
    char pad4[0x34 - 4];
    int model;
    int turret;
    char pad3C[0xC8 - 0x3C];
    unsigned short cost;
    char padCA[0xD0 - 0xCA];
} Vehicle;

typedef struct {
    char pad0[0x24];
    int x;
    int z;
    unsigned short heading;
    char pad2E[60 - 0x2E];
} Player;

typedef struct {
    char pad0[2];
    short link;
    char pad4[4];
    Owner *owner;
    char padC[64 - 12];
} Slot;

extern unsigned char D_800D3035;
extern unsigned char D_800D2FEC;
extern int D_800C60D0;
extern short D_800D326C;
extern Slot *D_800D3258;
extern Player *D_800D2FE4;
extern int D_800D2FE0;
extern int D_800AE94C;
extern int D_800AE950;
extern short D_800ADE54[][2];
extern short D_800ADE60[][2];
extern short D_800ADE6C[][2];
extern short D_800ADE78[][2];
extern short D_800ADE84[][2];
extern short D_800ADE90[][2];
extern short D_800ADE9C[][2];
extern short D_800ADEA8[][2];
extern int D_800ADEB4[];
extern int D_800ADEC0[];
extern int D_800ADECC;
extern int D_800ADED0;
extern int D_800ADED4;
extern int D_800ADED8;
extern int D_800ADE4C;
extern Vehicle D_800A4EF4[];
extern int func_80052784(Owner *owner, int *ids, unsigned char *enabled);
extern int func_80022814(void);
extern void func_80057C30(int tex, int mode, int x, int y, int sx, int sy, int *pal);
extern void func_80057A0C(int value, int mode, int x, int y, int sx, int sy, int digits, int *pal);
extern int func_8008AD60(int angle);
extern int func_8008ACC0(int angle);
extern void func_80069D68(int model, Vector *pos, int rx, int ry, int rz, int scale, int color);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_mul_t(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult\t%2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline Player *player_of(Owner *owner) {
    return &D_800D2FE4[owner->player];
}

void func_8006B5A4(Menu *menu) {
    Vector base;
    int ids[16];
    unsigned short angles[16];
    unsigned char enabled[16];
    int list[16];
    int slots[16];
    Vector pos;
    Owner *owner;
    Vehicle *v;
    int n;
    int k;
    unsigned short *p;
    int i;
    int count;
    int side;
    int offset;
    int scale;
    unsigned short heading;
    int show;
    int r;
    int d;
    unsigned char color;

    owner = menu->owner;
    count = 0;
    if (D_800D3035 != owner->player || owner->menu != menu) {
        return;
    }
    n = func_80052784(owner, ids, enabled);
    for (i = 0; i < n; i++) {
        if (enabled[i]) {
            list[count] = ids[i];
            slots[count] = i;
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    if (menu->cursor >= count) {
        menu->cursor = 0;
    }
    if (menu->count != count) {
        D_800ADED8 = menu->state == 0;
        D_800ADED4 = menu->owner->account->money;
        menu->cursor = 0;
        D_800ADECC = list[0];
        D_800ADED0 = D_800A4EF4[list[0]].cost;
    }
    menu->count = count;
    if (D_800C60D0 == 5) {
        if (D_800D2FEC == 1) {
            side = 2;
        } else {
            side = D_800D3035;
            if (side == 0) {
                D_800ADED8 = menu->state == 0;
                D_800ADED4 = menu->owner->account->money;
                D_800ADECC = list[menu->cursor];
                D_800ADED0 = D_800A4EF4[D_800ADECC].cost;
            }
        }
        if (D_800D326C != -1) {
            if (D_800D3258[D_800D326C].link == -1 && D_800D3258[D_800D326C].owner->player == 1) {
                D_800ADED8 = 0;
            }
        }
        if (menu->state == 0) {
            func_80057C30(D_800A4EF4[list[menu->cursor]].texture, 2, D_800ADE54[side][0], D_800ADE60[side][0],
                          D_800ADEB4[side], D_800ADEC0[side], &D_800ADE4C);
        }
        if (func_80022814() != 0 && side == 2) {
            func_80057C30(D_800AE94C, 2, D_800ADE90[2][0], D_800ADEA8[2][0], 4096, 4096, &D_800ADE4C);
            func_80057A0C(menu->owner->account->money, 2, D_800ADE9C[2][0], D_800ADEA8[2][0], 4096, 4096, 1,
                          &D_800ADE4C);
        }
        if (func_80022814() != 0 && menu->state == 0) {
            int cost = D_800A4EF4[list[menu->cursor]].cost;

            func_80057C30(D_800AE950, 2, D_800ADE6C[side][0], D_800ADE84[side][0], D_800ADEB4[side],
                          D_800ADEC0[side], &D_800ADE4C);
            func_80057A0C(cost, 2, D_800ADE78[side][0], D_800ADE84[side][0], D_800ADEB4[side], D_800ADEC0[side], 1,
                          &D_800ADE4C);
        }
        if (side == 1 && (show = D_800ADED8) == side) {
            func_80057C30(D_800A4EF4[D_800ADECC].texture, 2, D_800ADE54[0][0], D_800ADE60[0][0], D_800ADEB4[0],
                          D_800ADEC0[0], &D_800ADE4C);
            if (func_80022814() != 0) {
                func_80057C30(D_800AE950, 2, D_800ADE6C[0][0], D_800ADE84[0][0], D_800ADEB4[0], D_800ADEC0[0],
                              &D_800ADE4C);
                func_80057A0C(D_800ADED0, 2, D_800ADE78[0][0], D_800ADE84[0][0], D_800ADEB4[0], D_800ADEC0[0], show,
                              &D_800ADE4C);
            }
        }
    }
    offset = 0;
    p = angles;
    switch (menu->state) {
    case 1:
        offset = fixed_mul_t(0x10000 / menu->count, menu->timer);
        break;
    case 2:
        offset = -fixed_mul_t(0x10000 / menu->count, menu->timer);
        break;
    case 0:
        break;
    }
    for (k = 0; k < menu->count; k++) {
        p[k] = (0xFFFF / menu->count) * (k + menu->count - menu->cursor) + offset;
    }
    base.x = player_of(menu->owner)->x;
    base.z = player_of(menu->owner)->z;
    base.y = 0;
    heading = player_of(menu->owner)->heading;
    for (i = 0; i < count; i++) {
        scale = 4096;
        switch (menu->state) {
        case 0:
            if (i == menu->cursor) {
                scale = 8192;
            }
            break;
        case 1:
            if (i == menu->cursor) {
                scale = fixed_mul(menu->timer, -4096) + 8192;
            } else if (i == (menu->cursor + count - 1) % count) {
                scale = fixed_mul(menu->timer, 4096) + 4096;
            }
            break;
        case 2:
            if (i == menu->cursor) {
                scale = fixed_mul(menu->timer, -4096) + 8192;
            } else if (i == (menu->cursor + 1) % count) {
                scale = fixed_mul(menu->timer, 4096) + 4096;
            }
            break;
        }
        scale = fixed_mul(2048, scale);
        r = fixed_mul(0x1F4000, func_8008AD60(angles[i] >> 4));
        d = 0x4B0000 - fixed_mul(0x1F4000, func_8008ACC0(angles[i] >> 4));
        switch (heading) {
        case 0:
            pos.x = base.x + r;
            pos.z = base.z + d;
            break;
        case 0x4000:
            pos.x = base.x + d;
            pos.z = base.z - r;
            break;
        case 0x8000:
            pos.x = base.x - r;
            pos.z = base.z - d;
            break;
        case 0xC000:
            pos.x = base.x - d;
            pos.z = base.z + r;
            break;
        }
        pos.y = fixed_mul(-0x96000, func_8008ACC0(angles[i] >> 4)) + 0xB4000;
        v = &D_800A4EF4[list[i]];
        color = menu->owner->color;
        if (v->model != 107) {
            func_80069D68(v->model, &pos, 0, (D_800D2FE0 * 200) & 0xFFF8, 0, scale, color);
        }
        func_80069D68(D_800A4EF4[list[i]].turret, &pos, 0, (D_800D2FE0 * 200) & 0xFFF8, 0, scale, color);
    }
}
