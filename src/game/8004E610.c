typedef struct TransitionTank {
    char pad000[0xC0];
    void *target;
    char pad0C4[0x17C - 0xC4];
    int state;
    char pad180[0x188 - 0x180];
    int next_state;
} TransitionTank;
void func_80050370(TransitionTank *, int, void *, void *);
void func_8004E2AC(TransitionTank *, int);

void func_8004E610(TransitionTank *tank, void *context) {
    int state;

    switch (tank->state) {
    case 6:
    case 18:
    case 19:
    case 20:
    case 22:
        tank->state = 25;
        func_80050370(tank, 6, tank->target, context);
        break;
    case 9:
    case 11:
    case 12:
    case 13:
        state = tank->state;
        tank->state = 25;
        func_80050370(tank, state, tank->target, context);
        break;
    case 25:
        func_8004E2AC(tank, tank->next_state);
        return;
    default:
        return;
    }
}
