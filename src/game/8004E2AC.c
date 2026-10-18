typedef struct StateTank {
    char pad000[0x17C];
    int state;
} StateTank;
void func_8004E0BC(StateTank *);
void func_8004FAF4(StateTank *);
void func_8004E694(StateTank *, int);
void func_8004FBD4(StateTank *);
void func_8004FC20(StateTank *);
void func_8004FCF4(StateTank *);
void func_8004FE88(StateTank *, int);
void func_8004FFE0(StateTank *);
void func_8004FDD4(StateTank *, int, int);
void func_8004F388(StateTank *);
void func_8004EA1C(StateTank *);
void func_80050804(StateTank *, int);
void func_8005007C(StateTank *);
void func_800501C0(StateTank *);
void func_800502E4(StateTank *);

void func_8004E2AC(StateTank *tank, int state) {
    tank->state = state;
    switch (state) {
    case 0:
        func_8004E0BC(tank);
        break;
    case 1:
        func_8004FAF4(tank);
        break;
    case 24:
        func_8004E2AC(tank, 2);
        break;
    case 2:
        func_8004E694(tank, 0);
        break;
    case 3:
        func_8004E694(tank, 1);
        break;
    case 4:
        func_8004FBD4(tank);
        break;
    case 5:
        func_8004FC20(tank);
        break;
    case 6:
        func_8004FCF4(tank);
        break;
    case 9:
        func_8004FE88(tank, 1);
        break;
    case 17:
        func_8004FE88(tank, 0);
        break;
    case 22:
        func_8004FFE0(tank);
        break;
    case 7:
        func_8004FDD4(tank, 1, 6);
        break;
    case 8:
        func_8004FDD4(tank, 3, 6);
        break;
    case 23:
        func_8004F388(tank);
        break;
    case 10:
        func_8004EA1C(tank);
        break;
    case 11:
        func_80050804(tank, 2);
        break;
    case 12:
        func_80050804(tank, 1);
        break;
    case 13:
        func_80050804(tank, 4);
        break;
    case 14:
        func_8004FDD4(tank, 3, 11);
        break;
    case 15:
        func_8004FDD4(tank, 3, 12);
        break;
    case 16:
        func_8004FDD4(tank, 3, 13);
        break;
    case 18:
        func_8005007C(tank);
        break;
    case 19:
        func_800501C0(tank);
        break;
    case 20:
        func_800502E4(tank);
        break;
    case 29:
        break;
    }
}
