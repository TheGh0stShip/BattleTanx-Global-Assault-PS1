typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    void *data;
} Buffer;

typedef struct Playlist {
    unsigned char pad;
    unsigned char track[3];
    unsigned char cursor;
} Playlist;

extern unsigned char D_800AE9E8;
extern unsigned char D_800AEA40;
extern Buffer D_800EAFC0[];
extern Playlist D_800EAFB4;
extern char D_800EAF6C[];
extern void func_8008314C(void *, int);
extern void func_80082BEC(void *, int, int, void (*)());
extern void func_800762DC();

void func_80076370(int unused0, int unused1, int size, int ok) {
    Playlist *list;

    if (ok != 0 && size == 0x28004) {
        D_800EAFC0[D_800AE9E8].busy = 0;
        list = &D_800EAFB4;
        D_800AE9E8 = 100;
        list->track[list->cursor] = 0;
        list->cursor++;
        if (list->track[list->cursor] != 0 && list->cursor < 3) {
            func_8008314C(D_800EAF6C, 1);
            func_80082BEC(D_800EAF6C, (list->track[list->cursor] - 1) * 0x28004, 0, func_800762DC);
        } else {
            list->cursor = 0;
            D_800AEA40 = 1;
        }
    }
}
