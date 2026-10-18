typedef struct HitInfo { char pad0[4]; short kind; } HitInfo;
typedef struct ControlTank {
    char pad000[8];
    int x;
    char pad00C[4];
    int z;
    char pad014[0x98 - 0x14];
    int sound;
    char pad09C[0x218 - 0x9C];
    int status;
} ControlTank;
extern char D_800A4D24[];
void func_80053BB0(int, int, int, int);
void func_8008634C(int, void *, int);
void func_80047A34(ControlTank *tank, int damage, HitInfo *hit) {
    int amount;

    if (damage >= 2458) {
        amount = damage;
        if (hit != 0 && hit->kind == 4) {
            func_80053BB0(45, tank->x, tank->z, amount);
            func_8008634C(tank->sound, D_800A4D24, 0);
        } else {
            func_80053BB0(47, tank->x, tank->z, amount);
            if (tank->status & 2) {
                func_8008634C(tank->sound, D_800A4D24, 0);
            }
        }
    }
}
