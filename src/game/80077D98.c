typedef struct PadState {
    unsigned char ready;
    unsigned char port;
} PadState;

extern PadState D_800EBBB4;
extern int D_800EBC3C;
extern char D_800EBC54[];
extern unsigned int func_80088324(int, int, ...);

static inline unsigned char card_has_file(PadState *pad, char *info) {
    if (func_80088324(14, pad->port, D_800EBC54, info) != 0) {
        return 1;
    }
    return 0;
}

static inline unsigned char card_has_space(void) {
    if (func_80088324(3, D_800EBBB4.port) < 7932) {
        return 0;
    }
    return 1;
}

void func_80077D98(void) {
    PadState *pad = &D_800EBBB4;
    unsigned int status;
    char info[128];

    status = func_80088324(2, pad->port);
    if (!(status & 1)) {
        D_800EBC3C = 5;
        D_800EBBB4.ready = 0;
    } else if (!(status & 2)) {
        D_800EBC3C = 6;
        D_800EBBB4.ready = 0;
    } else {
        if (card_has_file(pad, info) || card_has_space()) {
            D_800EBBB4.ready = 1;
            D_800EBC3C = 3;
        } else {
            D_800EBBB4.ready = 0;
            D_800EBC3C = 7;
        }
    }
}
