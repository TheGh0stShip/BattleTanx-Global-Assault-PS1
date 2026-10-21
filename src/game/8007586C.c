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

extern unsigned char D_800AE9E8;
extern unsigned char D_800AE9E9;
extern int D_800EAFE0;
extern Buffer D_800EAFC0[];
extern Playlist D_800EAFB4;
extern char D_800EAF6C[];
extern char D_800AE9E0[];
extern void func_80083194(void *);
extern unsigned char func_80075570(void);
extern void func_8008314C(void *, int);
extern void func_80082798(void *, int, int);
extern void func_80082854(void *, void *, int);
extern void func_80082BEC(void *, int, int, void (*)(void));
extern void func_8007FC88(void *, void *);
extern void func_8007FA74(int);
extern void func_800757F0(void);
extern void func_800756A4(int);
extern void func_800762DC(void);

static inline unsigned char find_buffer(int track) {
    int i;

    for (i = 0; i < D_800AE9E9; i++) {
        if (*D_800EAFC0[i].data == track) {
            while (D_800EAFC0[i].busy != 0) {
            }
            return i;
        }
    }
    return 100;
}

static inline void stop_stream(void) {
    unsigned char j = 0;

    if (D_800AE9E8 != 100) {
        func_80083194(D_800EAF6C);
        *D_800EAFC0[0].data = 0;
        for (; j < 3; j++) {
            D_800EAFB4.track[j] = 0;
        }
        D_800EAFB4.state = 0;
        D_800EAFB4.cursor = 0;
    }
}

static inline void seek_track(unsigned char track) {
    func_8008314C(D_800EAF6C, 1);
    func_80082798(D_800EAF6C, (track - 1) * 0x28004, 0);
    func_8008314C(D_800EAF6C, 1);
}

static inline void start_buffer(unsigned char slot, int track) {
    func_8007FC88(D_800AE9E0, D_800EAFC0[slot].data + 1);
    func_8007FA74(0);
    D_800EAFE0 = D_800EAFC0[slot].data[0];
    func_800757F0();
    func_800756A4(track);
}

void func_8007586C(int track) {
    unsigned char slot;

    if (track == 0) {
        return;
    }
    if (D_800EAFE0 != track) {
        slot = find_buffer(track);
        if (slot == 100) {
            stop_stream();
            slot = func_80075570();
            seek_track(track);
            func_80082854(D_800EAF6C, D_800EAFC0[slot].data, 0x28004);
            start_buffer(slot, track);
        } else {
            start_buffer(slot, track);
        }
    } else {
        func_800757F0();
        if (D_800EAFB4.state != 0) {
            func_8008314C(D_800EAF6C, 1);
            func_80082BEC(D_800EAF6C, (D_800EAFB4.track[D_800EAFB4.cursor] - 1) * 0x28004, 0, func_800762DC);
            D_800EAFB4.state = 0;
        }
    }
}
