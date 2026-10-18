typedef struct {
    unsigned int state;
    int timer;
} Move;
typedef struct {
    char pad0[0x184];
    Move move;
    char pad18C[0x218 - 0x18C];
    int status;
} Tank;
extern int D_800D2FE0;
extern void func_8004E0BC(Tank *);
extern void func_8004D7D8(Tank *);
extern void func_80041464(Tank *, int);
extern void func_8004DD5C(Tank *);
extern void func_8004D804(Tank *);

void func_800508B0(Tank *tank) {
    Move *move = &tank->move;

    switch (move->state) {
    case 1:
        break;
    case 2:
        if (D_800D2FE0 >= move->timer) {
            func_8004E0BC(tank);
            func_8004D7D8(tank);
            move->state = 3;
            func_80041464(tank, 8);
        }
        break;
    case 3:
        if (!(tank->status & 8)) {
            move->state = 2;
            move->timer = D_800D2FE0 + 300;
            func_8004DD5C(tank);
            func_8004D804(tank);
        }
        break;
    case 4:
        if (D_800D2FE0 >= move->timer) {
            move->state = 5;
            func_80041464(tank, 13);
        }
        break;
    case 5:
        if (!(tank->status & 0x80)) {
            move->state = 4;
            move->timer = D_800D2FE0 + 150;
        }
        break;
    }
}
