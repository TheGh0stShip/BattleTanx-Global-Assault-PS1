extern void func_8009365C(int);
extern void func_800936D8(int);
extern void func_80093744(int);
extern void func_8009166C(void);
extern void func_80091604(void *);
extern unsigned int func_800976A0(unsigned char *);
extern int func_8009713C(int, unsigned char *, unsigned char *);

typedef struct {
    unsigned char active;
    char pad1[2];
    volatile unsigned char b3;
    volatile unsigned char b4;
    volatile unsigned char b5;
    volatile unsigned char b6;
    volatile unsigned char b7;
    volatile unsigned char b8;
    volatile unsigned char b9;
    volatile unsigned char b10;
    char pad11;
    unsigned int start;
    unsigned int cur;
    unsigned int end;
    char pad24[16];
    unsigned char result[8];
} S80093D6C;
extern S80093D6C D_800EEFAC;

void func_80093E24(unsigned char status, unsigned char *res);

void func_80093D6C(void) {
    S80093D6C *s = &D_800EEFAC;
    int need = 0;

    if (s->active != 0) {
        s->b6 = 0;
        s->b7 = 0;
        if (s->b3 != 0) {
            func_8009365C(5);
            need = 1;
        }
        if (s->b4 != 0) {
            func_800936D8(2);
        }
        if (s->b5 != 0) {
            func_80093744(5);
            need = 1;
        }
        if (s->b8 != 0) {
            need = 1;
            s->b8 = 0;
        }
        if (need) {
            func_8009166C();
        }
    }
}

void func_80093E24(unsigned char status, unsigned char *res) {
    S80093D6C *s;
    unsigned char loc[4];
    unsigned int pos;

    func_80091604(0);
    s = &D_800EEFAC;
    s->b8 = 0;
    if (status == 2) {
        s->b9 = 1;
        loc[0] = res[0];
        loc[1] = res[1];
        loc[2] = res[2];
        loc[3] = 1;
        pos = func_800976A0(loc) << 11;
        s->cur = pos;
        if (pos < s->start || pos >= s->end - 2048) {
            func_8009365C(2);
        }
    }
}

void func_80093EE0(unsigned int frames) {
    S80093D6C *a;
    S80093D6C *s;

    if (frames == 0) {
        return;
    }
    a = &D_800EEFAC;
    if (D_800EEFAC.active == 0 || a->b3 == 0 || a->b7 == 0 || a->b8 != 0 || a->b4 != 0 || a->b5 != 0) {
        return;
    }
    if (a->b10 != 0) {
        a->b10 = 0;
        a->b9 = 0;
        return;
    }
    if (a->b9 != 0 && frames < 32) {
        a->b9 = 0;
        return;
    }
    s = &D_800EEFAC;
    s->b9 = 1;
    s->b8 = 1;
    func_80091604(func_80093E24);
    if (func_8009713C(16, 0, s->result) == 0) {
        func_80091604(0);
        s->b9 = 0;
        s->b8 = 0;
    }
}
