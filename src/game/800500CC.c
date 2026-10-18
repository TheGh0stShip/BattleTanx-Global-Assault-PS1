typedef unsigned int u32;
typedef signed short s16;

typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    s16 generation;
    char pad002[0x1E];
    Vector position;
} Candidate;

typedef struct {
    u32 state;
    Candidate *candidate;
    int generation;
} MoveState;

typedef struct {
    char pad000[0xA4];
    void *active_object;
    char pad0A8[0xDC];
    MoveState move;
} Tank;

Candidate *func_80023870(int, int);
void func_8004E0BC(Tank *);
void func_8004E160(Tank *, Vector *, int, int);
void func_8004E2AC(Tank *, int);

void func_800500CC(Tank *tank) {
    Candidate *candidate;
    MoveState *move;

    if (tank->active_object != 0) {
        func_8004E2AC(tank, 20);
    } else {
        candidate = func_80023870(0, 8);
        move = &tank->move;
        switch (move->state) {
        case 1:
            if (candidate == 0) {
                move->candidate = 0;
                move->generation = 0;
            } else {
                move->candidate = candidate;
                move->generation = candidate->generation;
                func_8004E160(tank, &candidate->position, 0, 1);
                move->state = 2;
            }
            break;
        case 2:
            if (candidate == 0 || candidate != move->candidate ||
                candidate->generation != move->generation) {
                func_8004E0BC(tank);
                move->state = 1;
            }
            break;
        }
    }
}
