typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    u32 state;
    u32 next_state;
    int distance;
} MoveState;

typedef struct {
    char pad000[8];
    Vector position;
    char pad014[0x16C];
    u32 flags;
    MoveState move;
    Vector target;
} Tank;

int func_8004F934(Tank *);
int func_800495D8(Vector *, Vector *);
void func_8004E2AC(Tank *, int);

void func_800503B4(Tank *tank) {
    MoveState *move;

    move = &tank->move;
    switch (move->state) {
    case 1:
        if (func_8004F934(tank)) {
            move->state = 2;
        }
        break;
    case 2:
        if ((tank->flags & 1) ||
            func_800495D8(&tank->position, &tank->target) < move->distance) {
            func_8004E2AC(tank, move->next_state);
        }
        break;
    }
}
