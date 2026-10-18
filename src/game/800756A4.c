typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    int *data;
} Buffer;

typedef struct Playlist {
    unsigned char state;
    unsigned char track[3];
    unsigned char cursor;
} Playlist;

extern unsigned char D_800AE9E9;
extern unsigned char D_800AEA40;
extern Buffer D_800EAFC0[];
extern Playlist D_800EAFB4;
extern int D_800AE9EC[][3];

static inline unsigned char track_cached(int id) {
    unsigned char found = 0;
    unsigned char k;

    for (k = 0; k < D_800AE9E9; k++) {
        if (id == *D_800EAFC0[k].data) {
            found = 1;
            break;
        }
    }
    return found;
}

void func_800756A4(int set) {
    unsigned char count = 0;
    unsigned char j;

    for (j = count; j < 3; j++) {
        D_800EAFB4.track[j] = 0;
    }
    for (j = 0; j < 3; j++) {
        if (D_800AE9EC[set][j] == 0) {
            break;
        }
        if (!track_cached(D_800AE9EC[set][j])) {
            D_800EAFB4.track[count] = D_800AE9EC[set][j];
            count++;
        }
    }
    if (D_800EAFB4.track[0] != 0) {
        D_800EAFB4.state = 1;
        D_800EAFB4.cursor = 0;
        D_800AEA40 = 0;
    } else {
        D_800AEA40 = 1;
    }
}
