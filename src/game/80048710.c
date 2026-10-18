typedef struct AiTank {
    char pad000[0xE4];
    int next_fire;
    int next_pick;
    char pad0EC[0xEE - 0xEC];
    unsigned char weapon;
    unsigned char streak;
    char pad0F0[0x1EC - 0xF0];
    int skill;
    char pad1F0[0x258 - 0x1F0];
    int last_fire;
} AiTank;

extern int D_800D2FE0;

int func_8004D510(AiTank *);
int func_80048F90(AiTank *, int weapon);
unsigned int func_80086C84(void);
int func_800476F4(AiTank *, int weapon);
void func_80041464(AiTank *, int weapon);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

void func_80048710(AiTank *tank) {
    int weapon;
    int pick;
    int fire;

    if (tank->next_fire <= D_800D2FE0) {
        if (tank->next_pick > D_800D2FE0) {
            return;
        }
        weapon = func_8004D510(tank);
        if (func_80048F90(tank, weapon)) {
            pick = (func_80086C84() % 15 + 75) << 12;
            fire = pick - fixed_mul(fixed_mul(1024, tank->skill), pick);
        } else {
            pick = fixed_mul(tank->skill, func_800476F4(tank, weapon) << 12);
            fire = 0;
        }
        tank->next_pick = D_800D2FE0 + fixed_to_int(pick);
        tank->next_fire = D_800D2FE0 + fixed_to_int(fire);
        if (weapon != 0) {
            if (weapon == tank->weapon) {
                tank->streak++;
            } else {
                tank->weapon = weapon;
                tank->streak = 1;
            }
            tank->last_fire = D_800D2FE0;
            func_80041464(tank, weapon);
        }
    } else if (tank->last_fire + func_800476F4(tank, tank->weapon) < D_800D2FE0) {
        tank->last_fire = D_800D2FE0;
        func_80041464(tank, tank->weapon);
    }
}
