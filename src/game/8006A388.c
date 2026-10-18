typedef struct {
    int index;
    int timer;
    int c;
    int d;
} Timer;

typedef struct {
    char pad[0xC];
    int score;
    char pad10[8];
    int bonus;
} Hud;

typedef struct {
    char pad[0xC];
    Hud *hud;
} Globals;

extern Globals D_800E3E68;
extern Timer D_800ADD3C;
extern Timer D_800E53FC;
extern int D_800A6074;
extern int D_800A6070;
extern int D_800A68A4;
extern unsigned char D_800ABA5B;
extern char D_800ADD4C[];
extern int func_80090184(char *s);
extern void func_8006128C(int arg);

static inline void scramble(char *s) {
    char swap;

    swap = s[1];
    s[1] = s[5];
    s[5] = swap;
    swap = s[3];
    s[3] = s[8];
    s[8] = swap;
    swap = s[4];
    s[4] = s[7];
    s[7] = swap;
}

static inline int digit_value(char c) {
    int j;

    for (j = 0; j < 21; j++) {
        if (D_800ADD4C[j] == c) {
            break;
        }
    }
    return j;
}

int func_8006A388(char *code) {
    int digits[10];
    char buf[10];
    int i;
    int head;
    int mode;
    int level;
    int score;
    int bonus;
    Globals *g = &D_800E3E68;

    if (func_80090184(code) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        buf[i] = code[i];
    }
    scramble(buf);
    for (i = 0; i < 10; i++) {
        digits[i] = digit_value(buf[i]);
        if (digits[i] >= 21) {
            return 0;
        }
    }
    head = digits[1] * 21 + digits[0];
    mode = head & 3;
    level = head >> 2;
    if (mode == 0) {
        return 0;
    }
    if ((unsigned int)(level - 2) >= 55) {
        return 0;
    }
    score = 0;
    for (i = 4; i >= 2; i--) {
        score = score * 21 + digits[i];
    }
    if (score > 7000) {
        return 0;
    }
    if (score % 5 != 0) {
        return 0;
    }
    bonus = 0;
    for (i = 9; i >= 5; i--) {
        bonus = bonus * 21 + digits[i];
    }
    if (bonus > 4080000) {
        return 0;
    }
    D_800A6074 = mode;
    func_8006128C(D_800A68A4 + 0xE0);
    D_800ADD3C.index = level;
    D_800E53FC.index = level;
    D_800ADD3C.c = bonus;
    D_800ADD3C.d = bonus;
    D_800E53FC.c = bonus;
    D_800E53FC.d = bonus;
    D_800A6070 = 1;
    g->hud->bonus = bonus;
    D_800ABA5B = 0;
    D_800ADD3C.timer = score;
    D_800E53FC.timer = score;
    g->hud->score = score;
    return 1;
}
