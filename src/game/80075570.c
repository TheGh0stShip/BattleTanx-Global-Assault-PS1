typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    int *data;
} Buffer;

extern unsigned char D_800AE9E9;
extern int D_800EAFE0;
extern Buffer D_800EAFC0[];
extern int D_800AE9EC[][3];

static inline unsigned char track_in_set(int id) {
    unsigned char j;

    for (j = 0; j < 3; j++) {
        if (D_800AE9EC[D_800EAFE0][j] == id) {
            return 1;
        }
    }
    return 0;
}

unsigned char func_80075570(void) {
    unsigned char i;

    for (i = 0; i < D_800AE9E9; i++) {
        if (*D_800EAFC0[i].data == 0) {
            return i;
        }
    }
    for (i = 0; i < D_800AE9E9; i++) {
        if (!track_in_set(*D_800EAFC0[i].data) && *D_800EAFC0[i].data != D_800EAFE0) {
            return i;
        }
    }
    return 0;
}
