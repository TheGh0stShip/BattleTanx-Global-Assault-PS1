typedef struct Move {
    int dist;
    int speed;
    unsigned short heading;
    unsigned short pad0A;
    int pad0C;
    int arrived;
} Move;

typedef struct AiTank {
    char pad000[0x118];
    unsigned int boost;
    char pad11C[0x17C - 0x11C];
    int behavior;
    char pad180[0x210 - 0x180];
    int health;
    char pad214[0x218 - 0x214];
    int status;
} AiTank;

extern unsigned short D_800DE338;

void func_8004CF44(AiTank *);
void func_80050024(AiTank *, Move *);
void func_800504F0(AiTank *, Move *);
void func_8004FED0(AiTank *, Move *);
void func_80050668(AiTank *, Move *);
void func_80048900(AiTank *, Move *);
void func_80048F2C(AiTank *, Move *);
void func_80048AFC(AiTank *, Move *);
void func_8004D12C(AiTank *);
int func_80048FB0(AiTank *, Move *);
void func_80048710(AiTank *);

void func_80048D24(AiTank *tank) {
    Move move;

    move.dist = 0;
    move.speed = 0;
    move.heading = 0;
    move.pad0A = 0;
    move.pad0C = 0;
    move.arrived = 0;
    if (!(tank->status & 1) || tank->health <= 0) {
        return;
    }
    func_8004CF44(tank);
    if (tank->status & 0x100) {
        switch (tank->behavior) {
        case 23:
            func_80050024(tank, &move);
            break;
        case 26:
            func_800504F0(tank, &move);
            break;
        case 10:
            func_8004FED0(tank, &move);
            break;
        case 27:
        case 28:
            func_80050668(tank, &move);
            break;
        }
    } else {
        func_80048900(tank, &move);
        func_80048F2C(tank, &move);
        func_80048AFC(tank, &move);
    }
    if (!(tank->status & 1) || tank->health <= 0) {
        return;
    }
    func_8004D12C(tank);
    if (func_80048FB0(tank, &move)) {
        func_80048710(tank);
    }
    if (tank->boost < 400) {
        tank->boost += 100 / D_800DE338;
    }
}
