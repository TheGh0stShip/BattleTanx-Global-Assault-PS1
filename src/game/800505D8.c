typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SteeringState {
    int mode;
    int deadline;
    u16 speed;
    u16 heading;
    int value;
} SteeringState;

typedef struct Tank {
    u8 pad_000[0x2C];
    u16 heading;
    u8 pad_02E[0x184 - 0x2E];
    SteeringState steering;
    u8 pad_194[0x218 - 0x194];
    int flags;
    u8 pad_21C[0x2B8 - 0x21C];
    u16 field_2B8;
} Tank;

extern int D_800D2FE0;
extern int func_8004778C(u16, int, int);
extern void func_8004E0BC(Tank *);
extern void func_8004D7D8(Tank *);

void func_800505D8(Tank *tank, int delay, int supplied, int value) {
    SteeringState *steering;

    tank->flags |= 0x100;
    steering = &tank->steering;
    steering->deadline = D_800D2FE0 + delay;
    steering->speed = 0x1800;
    steering->heading = tank->heading;
    steering->value = value;
    if (supplied != 0)
        goto set_four;
    if (func_8004778C(tank->field_2B8, 0x24700F, 0) == 0)
        goto set_one;
set_four:
    steering->mode = 4;
    goto mode_done;
set_one:
    steering->mode = 1;
mode_done:
    func_8004E0BC(tank);
    func_8004D7D8(tank);
}
