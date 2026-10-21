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
extern unsigned char D_800AE9EA;
extern unsigned char D_800ABA5B;
extern int D_800EAFBC;
extern int D_800EAFE0;
extern Buffer D_800EAFC0[];
extern Playlist D_800EAFB4;
extern char D_800EAF6C[];
extern void func_80082424(void *, char *);
extern unsigned int func_80085F5C(int);
extern int *func_80068F34(int);
extern unsigned char func_80075570(void);
extern void func_8008314C(void *, int);
extern void func_80082798(void *, int, int);
extern void func_80082854(void *, void *, int);
extern void func_800756A4(int);

int func_80075AEC(void) {
    char name[20] = "\\assets\\fullscr.ful";
    int i = 0;
    unsigned char slot;

    func_80082424(D_800EAF6C, name);
    for (; func_80085F5C(-1) > 0x28004 && i < 4; i++) {
        D_800EAFC0[i].data = func_80068F34(0x28004);
        D_800EAFC0[i].data[0] = 0;
        D_800EAFC0[i].busy = 0;
    }
    D_800AE9E9 = i;
    D_800EAFE0 = 0;
    if (D_800ABA5B != 0) {
        D_800EAFBC = 6;
    } else {
        D_800EAFBC = 2;
    }
    {
        unsigned char *p;

        i = 2;
        p = &D_800EAFB4.state + i;
        for (; i >= 0; i--) {
            p[1] = 0;
            p--;
        }
    }
    D_800EAFB4.state = 0;
    D_800EAFB4.cursor = 0;
    slot = func_80075570();
    func_8008314C(D_800EAF6C, 1);
    func_80082798(D_800EAF6C, 0x28004, 0);
    func_8008314C(D_800EAF6C, 1);
    func_80082854(D_800EAF6C, D_800EAFC0[slot].data, 0x28004);
    func_800756A4(2);
    {
        int r = 1;

        D_800AE9EA = r;
        return r;
    }
}
