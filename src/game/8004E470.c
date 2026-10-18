typedef struct StateTank {
    char pad000[0x17C];
    int state;
} StateTank;
void func_8004FB40(StateTank *);
void func_8004FB48(StateTank *);
void func_8004FC18(StateTank *);
void func_8004FC5C(StateTank *);
void func_8004FD34(StateTank *);
void func_8004E888(StateTank *);
void func_8004F050(StateTank *);
void func_8004FE18(StateTank *);
void func_8004F534(StateTank *);
void func_8004EB50(StateTank *);
void func_800508B0(StateTank *);
void func_800500CC(StateTank *);
void func_80050204(StateTank *);
void func_8004ED14(StateTank *);
void func_800503B4(StateTank *);
void func_80050584(StateTank *);
void func_800506D8(StateTank *);

void func_8004E470(StateTank *tank) {
    switch (tank->state) {
    case 0:
        break;
    case 1:
        func_8004FB40(tank);
        break;
    case 2:
    case 3:
        func_8004FB48(tank);
        break;
    case 4:
        func_8004FC18(tank);
        break;
    case 5:
        func_8004FC5C(tank);
        break;
    case 6:
        func_8004FD34(tank);
        break;
    case 9:
        func_8004E888(tank);
        break;
    case 22:
        func_8004F050(tank);
        break;
    case 7:
    case 8:
    case 14:
    case 15:
    case 16:
        func_8004FE18(tank);
        break;
    case 23:
        func_8004F534(tank);
        break;
    case 10:
        func_8004EB50(tank);
        break;
    case 11:
    case 12:
    case 13:
        func_800508B0(tank);
        break;
    case 18:
        func_800500CC(tank);
        break;
    case 19:
        func_80050204(tank);
        break;
    case 20:
        func_8004ED14(tank);
        break;
    case 25:
        func_800503B4(tank);
        break;
    case 26:
        func_80050584(tank);
        break;
    case 27:
    case 28:
        func_800506D8(tank);
        break;
    case 29:
        break;
    }
}
