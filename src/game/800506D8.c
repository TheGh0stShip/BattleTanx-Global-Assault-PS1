typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 state;
    int deadline;
    u16 amount;
    u16 target_heading;
    int next_state;
} TurnState;

typedef struct {
    char pad000[0x2C];
    u16 heading;
    char pad02E[0x156];
    TurnState turn;
} Tank;

extern int D_800D2FE0;

u16 func_80047B98(u16, u16);
void func_8004E2AC(Tank *, int);

void func_800506D8(Tank *tank) {
    TurnState *turn;

    turn = &tank->turn;
    switch (turn->state) {
    case 1:
        if (D_800D2FE0 >= turn->deadline) {
            turn->state = 2;
        }
        break;
    case 2:
        if (turn->amount >= 513) {
            turn->amount -= 512;
        } else {
            turn->amount = 256;
            turn->state = 3;
        }
        break;
    case 3:
        if (turn->amount >= func_80047B98(tank->heading, turn->target_heading)) {
            tank->heading = turn->target_heading;
            turn->deadline = D_800D2FE0 + 90;
            turn->amount = 0;
            turn->state = 4;
        }
        break;
    case 4:
        if (D_800D2FE0 >= turn->deadline) {
            func_8004E2AC(tank, turn->next_state);
        }
        break;
    }
}
