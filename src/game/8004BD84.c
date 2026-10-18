typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Tracker {
    int object;
    u16 field_04;
    u16 field_06;
    u16 field_08;
    u8 pad_0A[2];
    u16 field_0C;
    u16 field_0E;
    u16 field_10;
    u16 field_12;
    u8 pad_14[8];
    int field_1C;
    int field_20;
    int field_24;
    u8 pad_28[4];
    int field_2C;
    int field_30;
    u8 pad_34[4];
    int field_38;
    int field_3C;
    int radius;
} Tracker;

typedef struct Tank {
    u8 pad_000[0x9C];
    int type;
    u8 pad_0A0[0xF8 - 0xA0];
    Tracker tracker;
} Tank;

typedef struct TankDefinition {
    u8 pad_00[0xA8];
    u16 reach;
    u8 pad_AA[0xD0 - 0xAA];
} TankDefinition;

extern TankDefinition D_800A4EF4[];
extern void func_8004C168(Tracker *);

void func_8004BD84(Tank *tank) {
    Tracker *tracker = &tank->tracker;
    tracker->object = 0;
    tracker->field_04 = 0;
    tracker->field_06 = 0;
    tracker->field_08 = 0;
    tracker->field_0C = 0;
    tracker->field_0E = 0;
    tracker->field_10 = 0;
    tracker->field_12 = 0;
    tracker->field_1C = 0;
    tracker->field_20 = 0;
    tracker->field_2C = 0;
    tracker->field_24 = 0;
    tracker->field_38 = 0;
    tracker->field_30 = 0;
    tracker->field_3C = 0;
    tracker->radius = (D_800A4EF4[tank->type].reach << 12) + 0x14000;
    func_8004C168(tracker);
}
