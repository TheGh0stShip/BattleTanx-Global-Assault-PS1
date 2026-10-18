typedef unsigned int u32;

typedef struct {
    u32 state;
    int deadline;
} MoveState;

typedef struct {
    char pad000[0x184];
    MoveState move;
    char pad18C[0x8C];
    u32 flags;
} Tank;

extern int D_800D2FE0;

void func_8004DD5C(Tank *);
void func_8004D804(Tank *);

void func_80050804(Tank *tank, u32 state) {
    MoveState *move;

    tank->flags &= ~0x100;
    move = &tank->move;

    switch (state) {
    case 1:
        move->state = state;
        move->deadline = D_800D2FE0;
        break;
    case 2:
        move->state = state;
        move->deadline = D_800D2FE0 + 600;
        break;
    case 4:
        move->state = state;
        move->deadline = D_800D2FE0 + 300;
        break;
    }

    func_8004DD5C(tank);
    func_8004D804(tank);
}
