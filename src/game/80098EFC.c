extern int func_800A2B78(void *, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_800991E8(void);

typedef struct {
    char pad0[76];
    int state;
    char pad80[12];
    int *slot;
    int value;
    char pad100[8];
    int arg108;
} S80098EFC;

void func_80098EFC(S80098EFC *p, unsigned char kind, int arg, int go) {
    int fresh;
    int cur;

    if (go != 0) {
        fresh = 1;
        if (kind == 4) {
            p->state = 5;
            if (p->slot != 0) {
                *p->slot = p->value;
            }
        } else {
            if (p->slot != 0) {
                cur = *p->slot;
                if (cur != 0 && cur != kind) {
                    fresh = 0;
                }
                *p->slot = kind;
            }
            p->arg108 = arg;
            p->state = 7;
        }
        if (func_800A2B78(p, fresh, func_800991E8) != 0) {
            return;
        }
    }
    func_80098D50(p, 1, 0);
}
