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
    char pad64[0x74 - 0x64];
    unsigned short credits;
    char pad76[0xAC - 0x76];
    int acc;
} Owner;

typedef struct {
    char pad0[8];
    Owner *owner;
    int count;
    int cursor;
    unsigned int state;
    int timer;
    unsigned char ready;
} Menu;

typedef struct {
    char pad0[4];
    unsigned short pressed;
    unsigned short held;
    char pad8[8];
    signed char stick;
    char pad11[140 - 17];
} Pad;

typedef struct {
    char pad0[200];
    unsigned short cost;
    char padCA[208 - 202];
} VehicleInfo;

extern Pad D_800EE028[];
extern int D_800A4D30[];
extern int D_800DE30C;
extern int D_800ADED8;
extern VehicleInfo D_800A4EF4[];
extern int func_80052784(Owner *owner, int *items, unsigned char *usable);
extern int func_80022814(void);
extern int func_80052A88(Owner *owner, int id, int mode);
extern void func_80052C64(Owner *owner, int id);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8006B23C(Menu *menu, int *done) {
    int items[16];
    unsigned char usable[16];
    int ids[16];
    int slots[16];
    unsigned short held;
    unsigned short pressed;
    signed char stick;
    int n;
    int i;
    int count;
    int id;

    held = D_800EE028[menu->owner->player].held;
    pressed = D_800EE028[menu->owner->player].pressed;
    stick = D_800EE028[menu->owner->player].stick;
    D_800A4D30[menu->owner->player] = 1;
    count = 0;
    if (menu->owner->menu != menu) {
        return;
    }
    n = func_80052784(menu->owner, items, usable);
    for (i = 0; i < n; i++) {
        if (usable[i] != 0) {
            ids[count] = items[i];
            slots[count] = i;
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    menu->count = count;
    if (menu->ready == 0) {
        menu->ready = 1;
    }
    if (count == 1) {
        menu->state = 0;
    }
    if (menu->cursor >= count) {
        menu->cursor = 0;
    }
    switch (menu->state) {
    case 1:
        menu->timer += fixed_mul(D_800DE30C, 163);
        if (menu->timer > 4096) {
            menu->state = 0;
            menu->timer = 0;
            menu->cursor--;
            if (menu->cursor == -1) {
                menu->cursor = count - 1;
            }
        }
        break;
    case 2:
        menu->timer += fixed_mul(D_800DE30C, 163);
        if (menu->timer > 4096) {
            menu->state = 0;
            menu->timer = 0;
            menu->cursor++;
            if (menu->cursor >= count) {
                menu->cursor = 0;
            }
        }
        break;
    case 0:
        if (held & 0x4000) {
            id = ids[menu->cursor];
            if (func_80052A88(menu->owner, id, func_80022814()) >= 0) {
                func_80052C64(menu->owner, id);
                *done = 1;
                D_800ADED8 = 0;
                menu->owner->acc = 0;
                if (func_80022814() != 0) {
                    unsigned short cost = D_800A4EF4[id].cost;

                    menu->owner->account->money -= cost;
                    menu->owner->credits -= cost;
                }
            }
        }
        if ((pressed & 0x80) || stick < -30) {
            menu->state = 2;
            menu->timer = 0;
        }
        if ((pressed & 0x20) || stick >= 31) {
            menu->state = 1;
            menu->timer = 0;
        }
        break;
    }
}
