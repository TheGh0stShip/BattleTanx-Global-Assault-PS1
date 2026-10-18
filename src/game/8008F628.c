extern int func_80099DEC(int, int, int);
extern void func_8008F504(unsigned char);
extern void func_8008F4B4(int);
extern void func_8008F628(void);
extern void func_8008F410(int);

typedef struct {
    char pad0[4];
    volatile int flags;
    char pad8[4];
    int ctl;
    char pad16[48];
    unsigned char esc;
    unsigned char quote;
} S8008F628;
extern S8008F628 D_800EEDF4;

void func_8008F628(void) {
    S8008F628 *s;
    S8008F628 *q;
    int status = func_80099DEC(0, 0, 0);
    int escaping;
    int c;

    s = &D_800EEDF4;
    escaping = s->esc != s->quote;
    if (status & 2) {
        q = s;
        do {
            q->ctl |= 2;
            c = func_80099DEC(0, 4, 0);
            if (!(status & 0x30)) {
                if (escaping) {
                    if ((c & 0xFF) == q->esc) {
                        q->flags |= 8;
                        func_8008F4B4(0);
                        goto next;
                    }
                    if ((c & 0xFF) == q->quote && !(q->flags & 0x40)) {
                        q->flags |= 0x40;
                        goto next;
                    }
                }
                if (q->flags & 0x40) {
                    c += q->quote;
                    q->flags &= ~0x40;
                }
                func_8008F504(c);
            } else {
                func_80099DEC(2, 1, 0);
                q->flags |= 1;
                func_8008F4B4(0);
            }
        next:
            status = func_80099DEC(0, 0, 0);
        } while (status & 2);
    }
}

void func_8008F7A0(void) {
    S8008F628 *s = &D_800EEDF4;

    s->ctl |= 4;
    func_8008F628();
    s->ctl &= ~4;
    func_80099DEC(1, 1, func_80099DEC(0, 1, 0) | 0x10);
    if (s->flags & 0x20) {
        func_8008F410(1);
    }
}
