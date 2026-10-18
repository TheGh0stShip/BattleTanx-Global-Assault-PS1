typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vector {
    int x;
    int y;
    int z;
    int pad;
} Vector;

typedef struct SteeringState {
    u8 pad_00[0x18];
    int dx;
    u8 pad_1C[4];
    int dz;
} SteeringState;

typedef struct Tank {
    u8 pad_000[8];
    Vector position;
    u8 pad_018[0x2C - 0x18];
    u16 heading;
    u8 pad_02E[0x3C - 0x2E];
    int field_03C;
    u8 pad_040[0x50 - 0x40];
    int field_050;
    u8 pad_054[0x184 - 0x54];
    SteeringState steering;
    u8 pad_1A8[0x2B8 - 0x1A8];
    u16 field_2B8;
} Tank;

typedef struct Move {
    int distance;
    int speed;
    u16 heading;
    u8 pad_0A[6];
    int arrived;
} Move;

extern void func_80048F2C(Tank *);
extern int func_80042F34(Tank *, int);
extern void func_8001E0A4(void *, u16, void *);

void func_800504F0(Tank *tank, Move *move) {
    move->distance = 0;
    move->heading = tank->heading;
    move->speed = 4096;
    move->arrived = 0;
    func_80048F2C(tank);
    if (func_80042F34(tank, 0x601008) == 0) {
        SteeringState *steering = &tank->steering;
        __asm__("" : "+r"(steering));
        tank->position.x += steering->dx;
        tank->position.z += steering->dz;
        tank->field_03C = 0;
        tank->field_050 = 0;
    }
    func_8001E0A4((u8 *)tank + 0x34, tank->field_2B8,
                  (u8 *)tank + 0x0C);
}
