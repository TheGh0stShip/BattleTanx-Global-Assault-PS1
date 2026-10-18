extern void func_80091A34(void);
extern void func_80093D6C(void);
extern void func_800916F4(void);
extern void func_80091604(void *);
extern void func_8009162C(void *);
extern void func_80091618(void *);
extern void func_8009759C(unsigned int, unsigned char *);
extern int func_800973AC(int, unsigned char *, unsigned char *);
extern void func_8009192C(void);
extern void func_8009194C(void);
extern int func_8009713C(int, unsigned char *, unsigned char *);
extern void func_8009365C(int);
extern void func_800937E4(void);


typedef struct {
    unsigned char active;
    volatile unsigned char stereo;
    char pad2;
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
    int len;
    char pad28[8];
    unsigned char filter[2];
    char pad38[10];
    int arg48;
    void (*done)(int);
} S80093960;
extern S80093960 D_800EEFAC;

int func_80093960(unsigned int pos, int len, int chan, int arg, void (*done)(int)) {
    S80093960 *s = &D_800EEFAC;
    S80093960 *t;
    unsigned char speed[8];
    unsigned char loc[8];
    int r = 0;
    int notify = 1;

    if (s->active != 0) {
        s->b6 = 0;
        s->b7 = 0;
        s->b9 = 0;
        func_80091A34();
        if (s->b3 != 0 || s->b4 != 0 || s->b5 != 0 || s->b8 != 0) {
            func_80093D6C();
        }
        func_800916F4();
        func_80091604(0);
        func_8009162C(0);
        func_80091618(0);
        *(int *)0x800C60BC = 1;
        func_8009759C(pos >> 11, loc);
        func_800973AC(2, loc, 0);
        if (D_800EEFAC.stereo != 0) {
            func_8009192C();
            speed[0] = 72;
        } else {
            func_8009194C();
            speed[0] = 200;
        }
        func_800973AC(14, speed, 0);
        t = &D_800EEFAC;
        t->filter[0] = 1;
        t->filter[1] = chan;
        func_800973AC(13, t->filter, 0);
        t->b3 = 1;
        t->b10 = 1;
        t->start = pos;
        t->cur = pos;
        t->end = pos + len;
        t->len = len;
        t->arg48 = arg;
        t->done = done;
        func_80091604(func_800937E4);
        if (func_8009713C(21, loc, 0) != 0) {
            r = 1;
        } else {
            func_8009365C(5);
            notify = 0;
        }
    }
    if (r == 0 && notify != 0 && done != 0) {
        done(0);
    }
    return r;
}
