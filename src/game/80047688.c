typedef struct ControlTank {
    char pad000[0x218];
    int status;
    char pad21C[0x584 - 0x21C];
    unsigned int control_state;
    int control_time;
} ControlTank;

extern int D_800D2FE0;

int func_80047688(ControlTank *tank) {
    if (tank->status & 8) {
        return 0;
    }
    switch (tank->control_state) {
    case 0:
    case 2:
    case 3:
        return 1;
    case 1:
        if (D_800D2FE0 - tank->control_time < 45) {
            return 1;
        }
        break;
    }
    return 0;
}
