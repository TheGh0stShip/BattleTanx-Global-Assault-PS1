typedef struct ReadState {
    int unk0;
    int unk4;
    unsigned long *volatile addr;
    int unkC;
    volatile int size;
    volatile int remaining;
    volatile int time;
    int start;
    volatile int pos;
    int cb0;
    int cb1;
    int cb2;
    int mode;
    unsigned char *volatile result;
} ReadState;

extern ReadState D_800B90BC;
extern void (*D_800B90B8)(int status, unsigned char *result);
extern char D_800C5F98[];
extern void func_800A1454(void);
extern void func_80097558(int cb);
extern void func_80097538(void *buf, int n);
extern void func_80097518(void *buf, int n);
extern void func_8009757C(int a);
extern int func_800976A0(void *hdr);
extern void func_80096F9C(char *fmt, ...);
extern int func_80088870(int mode);
extern void func_800A1520(int a);
extern void func_80097114(int a);
extern void func_80097128(int a);
extern void func_80097278(int a, int b);

void func_800A11F4(unsigned char intr, unsigned char *result) {
    ReadState *rs = &D_800B90BC;
    unsigned long hdr[3];

    rs->result = result;
    if (intr == 1) {
        if (rs->remaining > 0) {
            if (rs->size == 512) {
                if (D_800B90BC.mode & 1) {
                    func_80097558(0);
                    func_80097538(hdr, 3);
                    func_8009757C(0);
                    func_80097558((int)func_800A1454);
                } else {
                    func_80097518(hdr, 3);
                }
                if (func_800976A0(hdr) != D_800B90BC.pos) {
                    ReadState *q;

                    func_80096F9C(D_800C5F98);
                    q = &D_800B90BC;
                    q->remaining = -1;
                }
            }
            if (D_800B90BC.mode & 1) {
                func_80097538(D_800B90BC.addr, D_800B90BC.size);
            } else {
                ReadState *q = &D_800B90BC;

                func_80097518(D_800B90BC.addr, D_800B90BC.size);
                q->addr = D_800B90BC.addr + D_800B90BC.size;
                q->remaining--;
                q->pos++;
            }
        }
    } else {
        D_800B90BC.remaining = -1;
    }
    {
    ReadState *p = &D_800B90BC;

    p->time = func_80088870(-1);
    if (p->remaining < 0) {
        func_800A1520(1);
    }
    if (func_80088870(-1) > p->start + 1200) {
        p->remaining = -1;
    }
    if (p->remaining == 0 || func_80088870(-1) > p->start + 1200) {
        func_80097114(p->cb0);
        func_80097128(p->cb1);
        if (p->mode & 1) {
            func_80097558(p->cb2);
        }
        func_80097278(9, 0);
        if (D_800B90B8 != 0) {
            D_800B90B8(p->remaining == 0 ? 2 : 5, result);
        }
    }
    }
}
