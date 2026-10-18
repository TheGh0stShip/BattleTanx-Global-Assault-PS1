typedef struct {
    unsigned short pad0[2];
    unsigned short enabled;
    unsigned short expired;
    unsigned short pad8[17];
    unsigned short timers[16];
    unsigned short reload[16];
    unsigned short step[16];
    unsigned short pad8a;
} TimerBank;

extern TimerBank D_800EE028[];

void func_80083F6C(int bank, int dt)
{
    int bit;
    int i;

    for (i = 0, bit = 1; i < 16; i++, bit <<= 1) {
        if (D_800EE028[bank].timers[i] != 0) {
            if (D_800EE028[bank].enabled & bit) {
                int t = D_800EE028[bank].timers[i] - (unsigned short)dt;
                if (t <= 0) {
                    t += D_800EE028[bank].step[i];
                    if (t <= 0) {
                        t = 1;
                    }
                    D_800EE028[bank].timers[i] = t;
                    D_800EE028[bank].expired |= bit;
                } else {
                    D_800EE028[bank].timers[i] = t;
                }
            } else {
                D_800EE028[bank].timers[i] = D_800EE028[bank].reload[i];
            }
        }
    }
}
