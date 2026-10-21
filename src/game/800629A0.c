typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Tank {
    char pad0[8];
    Vector pos;
    char pad1[0x98 - 0x14];
    unsigned short kind;
    char pad2[0xA4 - 0x9A];
    int active;
} Tank;

typedef struct Holder {
    int pad[2];
    Tank *tank;
} Holder;

typedef struct Pickup {
    int pad[3];
    Vector pos;
    unsigned char kind;
} Pickup;

typedef struct Shot {
    int pad[3];
    int state;
    int pad2[4];
    Vector pos;
    int pad3;
    unsigned char kind;
} Shot;

typedef struct Game {
    int pad;
    int state;
    int pad2[2];
    int time;
} Game;

typedef struct Timer {
    int pad;
    unsigned short limit;
} Timer;

extern unsigned int D_800C60D0;
extern unsigned char D_800ABA60[];
extern Game D_800D2FE4;
extern Timer *D_800E3E74;
extern void *func_80023870(void *, int);
extern int func_80047688(Tank *);
extern unsigned short func_80062384(Vector *, unsigned short, unsigned short, unsigned short, int);

static inline unsigned short show_plain(Vector *v, int player, int count) {
    return func_80062384(v, player, 0, count, 16);
}

void func_800629A0(Tank *self, int player_arg) {
    int count;
    int player;
    Holder *holder;
    Tank *tank;
    Pickup *pickup;
    Shot *shot;
    Vector pos;
    int flag;

    count = 0;
    player = player_arg;
    if (D_800C60D0 < 10) {
        if (D_800C60D0 >= 7) {
            D_800ABA60[(unsigned short)player] = 0;
            return;
        }
    }
    for (holder = func_80023870(0, 4); holder != 0; holder = func_80023870(holder, 4)) {
        int lift = 0x118000;

        tank = holder->tank;
        if (tank != 0 && tank != self && func_80047688(tank)) {
            pos.x = tank->pos.x;
            pos.y = tank->pos.y + lift;
            pos.z = tank->pos.z;
            flag = 0;
            if (tank->active != 0) {
                flag = 288;
            }
            if (func_80062384(&pos, player, tank->kind, count, flag)) {
                count++;
            }
        }
    }
    for (pickup = func_80023870(0, 21); pickup != 0; pickup = func_80023870(pickup, 21)) {
        int lift = 0x118000;

        pos.x = pickup->pos.x;
        pos.y = pickup->pos.y + lift;
        pos.z = pickup->pos.z;
        if (func_80062384(&pos, player, pickup->kind, count, 16)) {
            count++;
        }
    }
    for (shot = func_80023870(0, 8); shot != 0; shot = func_80023870(shot, 8)) {
        int lift = 0x118000;

        if (shot->state != 2) {
            pos.x = shot->pos.x;
            pos.y = shot->pos.y + lift;
            pos.z = shot->pos.z;
            if (func_80062384(&pos, player, shot->kind, count, 32)) {
                count++;
            }
        }
        __asm__("" : "=r"(shot) : "0"(shot));
    }
    if ((D_800D2FE4.state == 7 && D_800D2FE4.time <= D_800E3E74->limit) || D_800D2FE4.state == 14) {
        for (pickup = func_80023870(0, 20); pickup != 0; pickup = func_80023870(pickup, 20)) {
            int lift = 0x118000;

            pos.x = pickup->pos.x;
            pos.y = pickup->pos.y + lift;
            pos.z = pickup->pos.z;
            if (show_plain(&pos, player, count)) {
                count++;
            }
        }
    }
    D_800ABA60[(unsigned short)player] = count;
}
