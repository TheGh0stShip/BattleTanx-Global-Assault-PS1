typedef struct TankSpawn {
    char pad00[0x18];
    int mode;
    int slot;
} TankSpawn;

typedef struct Tank {
    char pad000[0x8];
    int x;
    char pad00C[0x4];
    int z;
    char pad014[0x94 - 0x14];
    int respawn_link;
    char pad098[0x9C - 0x98];
    int zone;
    char pad0A0[0xA8 - 0xA0];
    int team_bit;
    char pad0AC[0xB4 - 0xAC];
    int path_index;
    char path[0xD8 - 0xB8];
    char steer[0x170 - 0xD8];
    int last_x;
    char pad174[0x178 - 0x174];
    int last_z;
    int behavior;
    int behavior_flags;
    char pad184[0x218 - 0x184];
    int status;
} Tank;

enum TankMessage {
    TANK_SPAWN,
    TANK_REMOVE,
    TANK_DEACTIVATE,
    TANK_RESPAWN
};

extern int D_800E3CC0;
extern void *D_800A5B24;

void func_8004DFC0(void *path);
void func_8004D7B0(void *steer);
void func_8004E5C0(int *behavior);
void func_800393C0(Tank *, int slot);
void func_8004BD84(Tank *);
void func_8004CEF4(Tank *);
void func_8004E2AC(Tank *);
void func_8004E5CC(Tank *);
void func_8004D0A0(Tank *);
void func_80049D38(Tank *);
void func_8004BF64(Tank *);
void func_8004D134(Tank *);
void func_800505D8(Tank *, int, int, int);

void func_80047BB8(Tank *tank, unsigned int message, TankSpawn *spawn) {
    switch (message) {
    case TANK_SPAWN:
        tank->behavior_flags = 0;
        tank->path_index = 0;
        func_8004DFC0(tank->path);
        func_8004D7B0(tank->steer);
        func_8004E5C0(&tank->behavior);
        func_800393C0(tank, spawn->slot);
        func_8004BD84(tank);
        func_8004CEF4(tank);
        tank->last_x = tank->x;
        tank->last_z = tank->z;
        message = spawn->mode;
        if (message - 7 < 2 || message == 14 || message == 15 || message == 16) {
            func_8004E2AC(tank);
        } else {
            func_8004E5CC(tank);
        }
        if (tank->status & 2) {
            D_800E3CC0 |= tank->team_bit;
        } else {
            func_8004D0A0(tank);
        }
        break;
    case TANK_REMOVE:
        func_80049D38(tank);
        if (D_800A5B24 != 0) {
            func_8004BF64(tank);
        }
        func_8004D134(tank);
        if (tank->status & 2) {
            D_800E3CC0 &= ~tank->team_bit;
        }
        break;
    case TANK_DEACTIVATE:
        func_80049D38(tank);
        if (D_800A5B24 != 0) {
            func_8004BF64(tank);
        }
        break;
    case TANK_RESPAWN:
        tank->path_index = 0;
        func_8004DFC0(tank->path);
        func_8004D7B0(tank->steer);
        if (tank->respawn_link == 0) {
            func_8004E5C0(&tank->behavior);
            tank->last_x = tank->x;
            tank->last_z = tank->z;
            if (tank->zone == 11) {
                tank->behavior_flags |= 0x20;
            } else {
                tank->behavior = 28;
                func_800505D8(tank, 0, 1, 6);
            }
        }
        break;
    }
}
