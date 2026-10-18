typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SteeringState {
    int mode;
    int deadline;
    int magnitude;
    int x;
    u8 pad_10[4];
    int z;
    u8 pad_18[0x24 - 0x18];
    int value;
} SteeringState;

typedef struct Tank {
    u8 pad_000[8];
    int x;
    u8 pad_00C[4];
    int z;
    u8 pad_014[0x2C - 0x14];
    u16 heading;
    u8 pad_02E[0x184 - 0x2E];
    SteeringState steering;
    u8 pad_1AC[0x218 - 0x1AC];
    int flags;
} Tank;

extern int D_800D2FE0;
extern void func_80049680(void *, int, u16);
extern void func_8004E0BC(Tank *);
extern void func_8004D7D8(Tank *);

void func_80050454(Tank *tank, int value) {
    SteeringState *steering;

    tank->flags |= 0x100;
    steering = &tank->steering;
    steering->mode = 1;
    steering->magnitude = 0xFA000;
    steering->deadline = D_800D2FE0 + 60;
    steering->x = tank->x;
    steering->z = tank->z;
    func_80049680((u8 *)tank + 0x19C, 0xF000, tank->heading);
    steering->value = value;
    func_8004E0BC(tank);
    func_8004D7D8(tank);
}
