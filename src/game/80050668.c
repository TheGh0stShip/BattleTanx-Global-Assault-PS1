typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SteeringState {
    u8 pad_00[8];
    u16 turn;
} SteeringState;

typedef struct Tank {
    u8 pad_000[0x2C];
    u16 heading;
    u8 pad_02E[2];
    u16 turn_accumulator;
    u8 pad_032[0x9C - 0x32];
    int type;
    u8 pad_0A0[0x184 - 0xA0];
    SteeringState steering;
} Tank;

typedef struct Output {
    u8 pad_00[12];
    int field_0C;
} Output;

typedef struct TankDefinition {
    u8 pad_00[0x10];
    int flags;
    u8 pad_14[0xD0 - 0x14];
} TankDefinition;

extern TankDefinition D_800A4EF4[];

void func_80050668(Tank *tank, Output *output) {
    SteeringState *steering;

    output->field_0C = 0;
    steering = &tank->steering;
    tank->heading -= steering->turn;
    if (D_800A4EF4[tank->type].flags & 1)
        tank->turn_accumulator += steering->turn * 2;
}
