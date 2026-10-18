typedef struct Tank {
    char pad0[0x2C];
    unsigned short heading;
    unsigned short pad2E;
    unsigned short turret;
    char pad32[0x34 - 0x32];
    char body[0x4C - 0x34];
    unsigned short speed;
    char pad4E[0x98 - 0x4E];
    int player;
    int type;
    char padA0[0x218 - 0xA0];
    int status;
    char pad21C[0x22C - 0x21C];
    unsigned short ammo[17];
    char pad24E[0x250 - 0x24E];
    int weapon[2];
    int last_fire[2];
    int switch_time;
    char pad264[0x580 - 0x264];
    int recoil;
    int control;
    int control_time;
} Tank;

typedef struct VehicleInfo {
    char pad0[0x5C];
    int rate;
    char pad60[0xD0 - 0x60];
} VehicleInfo;

extern int D_800A4D30[];
extern VehicleInfo D_800A4EF4[];
extern unsigned char D_800AED53;
extern unsigned char D_800AED4A;
extern int D_800D2FE0;
extern int func_80041464(Tank *, int);
extern void func_8001F094(void *, int, int);
extern void func_80063C68(void *, int, int);

void func_80042BAC(Tank *tank, int slot) {
    int weapon;
    int elapsed;
    int limit;
    int rate;
    int next;
    int start;
    short kick;
    int step;

    weapon = tank->weapon[slot];
    if (D_800A4D30[tank->player] != 0) {
        return;
    }
    if (tank->ammo[weapon] == 0) {
        return;
    }
    elapsed = D_800D2FE0 - tank->last_fire[slot];
    switch (weapon) {
    case 1:
        rate = D_800A4EF4[tank->type].rate >> 12;
        if ((tank->status & 2) && (D_800AED53 & 1)) {
            if (rate > 5) {
                rate = 5;
            }
        }
        limit = rate;
        break;
    case 12:
        limit = 5;
        break;
    default:
        limit = 30;
        break;
    }
    if (elapsed < limit) {
        return;
    }
    if (func_80041464(tank, weapon) < 0) {
        return;
    }
    switch (weapon) {
    case 6:
    case 8:
    case 10:
    case 11:
    case 13:
    case 15:
    case 16:
        break;
    default:
        switch (tank->control) {
        case 1:
            tank->control = 3;
            tank->recoil = 0x14000;
            tank->control_time = D_800D2FE0;
            break;
        case 3:
            tank->recoil = 0x14000;
            tank->control_time = D_800D2FE0;
            break;
        }
        break;
    }
    tank->last_fire[slot] = D_800D2FE0;
    switch (slot) {
    case 0:
        if (!(D_800AED4A & 1)) {
            tank->ammo[weapon]--;
        }
        switch (tank->type) {
        case 1:
            kick = -35;
            break;
        case 5:
            kick = -14;
            break;
        case 0:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 10:
            kick = -70;
            break;
        case 16:
        default:
            kick = 0;
            break;
        }
        if (kick != 0) {
            func_8001F094(tank->body, (kick * tank->speed) << 12,
                          (unsigned short)(tank->heading + tank->turret));
        }
        break;
    case 1:
        if (!(D_800AED4A & 1)) {
            tank->ammo[weapon]--;
        }
        if (tank->ammo[weapon] == 0) {
            start = tank->weapon[1];
            if (start != 0) {
                next = start;
                step = 14;
                do {
                    next = (next + step) % 15 + 2;
                } while (next != start && tank->ammo[next] == 0);
                if (tank->ammo[next] == 0) {
                    next = 0;
                    tank->weapon[1] = 0;
                    func_80063C68(0, *(unsigned short *)&tank->player, next);
                } else {
                    tank->weapon[1] = next;
                    func_80063C68(&tank->ammo[next], *(unsigned short *)&tank->player, next);
                }
                tank->switch_time = D_800D2FE0;
            }
        }
        break;
    }
}
