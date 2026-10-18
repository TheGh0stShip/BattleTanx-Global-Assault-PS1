extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern int D_800EF124;

typedef struct S80098D50 {
    char pad0[76];
    int state;
    char pad80[4];
    int flushed;
    unsigned char kind;
    char pad89[11];
    int arg100;
    char pad104[4];
    int arg108;
    void (*flush)(struct S80098D50 *, int, int);
    void (*done)(struct S80098D50 *, int, int, int, int);
} S80098D50;

void func_80098D50(S80098D50 *p, int result, int aborted) {
    void (*done)(struct S80098D50 *, int, int, int, int);

    D_800EF124 = 0;
    p->state = 0;
    if (aborted == 0) {
        if (func_800A2CB8(p, 0) == 0) {
            func_800A2DC8(p);
        }
    } else if (p->flush != 0 && p->flushed != 0) {
        p->flush(p, 0, result);
        p->flushed = 0;
    }
    done = p->done;
    p->done = 0;
    if (done != 0) {
        done(p, p->kind, p->arg100, p->arg108, aborted);
    }
}
