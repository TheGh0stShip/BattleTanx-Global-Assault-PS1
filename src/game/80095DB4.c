typedef struct {
    char name[20];
    int attr;
    int size;
    void *next;
    int head;
    char system[4];
} CardDirEntry;

typedef struct {
    int state;
    int result;
    int f8;
    int chan;
} CardState;

extern CardState D_800EF094;
extern int D_800EF090;
extern int D_800EF0E8;
extern char D_800C5368[];
extern char D_800C5218[];
extern int func_800943B0(char *);
extern void func_80096714(int, char *);
extern char *func_8008D954(char *, char *);
extern int func_8009F75C(char *, CardDirEntry *);
extern int func_8009F76C(CardDirEntry *);
extern int func_80096008(int);
extern int func_8009601C(int, int *, int *);
extern void func_8009F5AC(int (*)(int *));
extern int func_800950D4(int *);

static inline int card_start_format(CardState *p, int chan)
{
    if (p->state != 0) {
        func_800943B0(D_800C5218);
        return 0;
    }
    p->state = 2;
    p->result = 0;
    p->f8 = 0;
    D_800EF094.chan = chan;
    func_8009F5AC(func_800950D4);
    return 1;
}

static inline void store_count(int **pc, int n)
{
    if (*pc != 0) {
        **pc = n;
    }
}

int func_80095DB4(int chan, char *path, CardDirEntry *out, int *count, int skip, int max)
{
    char name[32];
    CardDirEntry d;
    int result;
    int retry;
    int i;
    int n;
    int r;
    CardState *cs;

    cs = &D_800EF094;
    __asm__("" : "=r"(cs) : "0"(cs));
    if (cs->state != 0) {
        func_800943B0(D_800C5368);
        return -1;
    }
    func_80096714(chan, name);
    func_8008D954(name, path);
    retry = 0;
    result = 0;
    D_800EF090 |= 1 << cs->chan;
    n = 0;
    i = 0;
    if (skip + max > 0) {
        do {
            __asm__("" : : "r"(i));
            __asm__("" : : "r"(i));
            __asm__("" : : "r"(i));
            __asm__("" : : "r"(i));
            if (i == 0) {
                while ((r = func_8009F75C(name, &d)) == 0) {
                    D_800EF0E8 = func_80096008(0);
                    card_start_format(cs, chan);
                    func_8009601C(0, 0, &result);
                    func_80096008(D_800EF0E8);
                    if (result == 0) {
                        break;
                    }
                    __asm__("" : : "r"(retry));
                    __asm__("" : : "r"(retry));
                    __asm__("" : : "r"(retry));
                    __asm__("" : : "r"(retry));
                    if (++retry >= 16) {
                        return result;
                    }
                }
                if (r == 0) {
                    break;
                }
            } else if (func_8009F76C(&d) == 0) {
                break;
            }
            if (i >= skip && out != 0) {
                out[n] = d;
                n++;
            }
            i++;
        } while (i < skip + max);
    }
    store_count(&count, n);
    return 0;
}
