typedef struct {
    int index;
    int timer;
    int c;
    int d;
} Timer;

typedef struct {
    char pad[0xC];
    int timer;
    char pad10[8];
    int value;
} Hud;

extern Timer D_800ADD3C;
extern Timer D_800E53FC;
extern unsigned short D_800A60D8;
extern int D_800A60D4;
extern Hud *D_800E3E74;
extern unsigned int D_800A6074;

void func_8006A290(void) {
    int time = 0;

    if (D_800ADD3C.timer != -1) {
        D_800E53FC = D_800ADD3C;
        D_800ADD3C.timer = -1;
        return;
    }
    D_800E53FC.index = 0;
    if (D_800A60D8 != 0) {
        D_800E53FC.index = D_800A60D4 - 1;
    }
    D_800E53FC.d = 0;
    D_800E53FC.c = 0;
    D_800E3E74->value = 0;
    switch (D_800A6074) {
    case 1:
        time = 90;
        break;
    case 2:
        time = 60;
        break;
    case 3:
        time = 30;
        break;
    }
    D_800E53FC.timer = time;
    D_800E3E74->timer = time;
}
