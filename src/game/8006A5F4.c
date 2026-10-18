typedef struct {
    int w0;
    int w1;
} Code;

typedef struct {
    char pad[0xC];
    int score;
    char pad10[8];
    int bonus;
} Hud;

extern Hud *D_800E3E74;
extern int D_800E53FC;
extern int D_800A6074;
extern char D_800ADD4C[];

static inline void encode_digits(char *dst, int start, int value, int count) {
    int i;

    for (i = 0; i < count; i++) {
        dst[start + i] = D_800ADD4C[value % 21];
        value /= 21;
    }
    dst[start + count] = 0;
}

Code func_8006A5F4(char *out) {
    Code code;
    int score;
    int bonus;
    int value;
    int level;
    char swap;

    code.w1 = 0;
    code.w0 = 0;
    score = D_800E3E74->score;
    if (score > 7000) {
        score = 7000;
    }
    bonus = D_800E3E74->bonus;
    if (bonus > 4080000) {
        bonus = 4080000;
    }
    code.w1 = bonus;
    level = (D_800E53FC & 0x3F) << 2;
    code.w0 = level;
    value = level | (D_800A6074 & 3);
    code.w0 = (value << 13) | (score & 0x1FFF);
    encode_digits(out, 0, value, 2);
    encode_digits(out, 2, score, 3);
    encode_digits(out, 5, bonus, 5);
    swap = out[1];
    out[1] = out[5];
    out[5] = swap;
    swap = out[3];
    out[3] = out[8];
    out[8] = swap;
    swap = out[4];
    out[4] = out[7];
    out[7] = swap;
    return code;
}
