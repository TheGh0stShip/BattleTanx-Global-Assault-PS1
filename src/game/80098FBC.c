extern int func_800A2A98(void *, void *, int, int, int, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_800991E8(void);

typedef struct {
    char pad0[76];
    int state;
    char pad80[8];
    char buf[12];
    int a;
    int b;
    int c;
} S80098FBC;

void func_80098FBC(S80098FBC *p, unsigned char kind, int a2, int go) {
    if (go != 0) {
        if (kind != 1) {
            go = 0;
        }
        if (go != 0) {
            p->state = 6;
            if (func_800A2A98(p, p->buf, p->a, p->b, p->c, 1, func_800991E8) != 0) {
                return;
            }
        }
    }
    func_80098D50(p, 1, 0);
}
