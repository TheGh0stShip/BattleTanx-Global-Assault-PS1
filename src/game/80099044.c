extern int func_800A2B78(void *, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_800991E8(void);

typedef struct S80099044 {
    char pad0[76];
    int state;
    char pad80[4];
    int flushed;
    char pad88[24];
    void (*flush)(struct S80099044 *, int, int);
} S80099044;

void func_80099044(S80099044 *p, unsigned char kind, int a2, int go) {
    if (go != 0) {
        if (kind == 4) {
            if (p->flush != 0) {
                p->flush(p, 1, 1);
                p->flushed = 1;
            }
        }
        p->state = 5;
        if (func_800A2B78(p, kind == 4, func_800991E8) != 0) {
            return;
        }
    }
    func_80098D50(p, 1, 0);
}
