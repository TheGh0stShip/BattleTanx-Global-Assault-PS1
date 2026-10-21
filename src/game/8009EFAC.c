typedef struct {
    unsigned char len;
    char pad1[3];
    unsigned char *data;
} CardEntry;

typedef struct {
    unsigned short *words;
    unsigned char *recs;
    CardEntry *ents;
    char padC[8];
    void *start;
    void *step;
    char pad1C[0x20];
    unsigned char *rx;
    char pad40[6];
    unsigned char state;
    unsigned char index;
    unsigned char remain;
    unsigned char phase;
    char pad4A[0x99];
    unsigned char nwords;
    char padE4[5];
    unsigned char nrecs;
    unsigned char nents;
} CardReq;

extern int (*D_800B8C90)(void);
extern unsigned char *D_800EFC58;
extern void func_8009F51C(CardReq *p, int i);
extern void func_8009F53C(CardReq *p, int i);
extern void func_8009F55C(CardReq *p, int i);
extern void func_8009F57C(CardReq *p);
void func_8009F080(CardReq *p);
int func_8009F128(CardReq *p);

int func_8009EFAC(CardReq *p, int size) {
    int n;
    int ret;
    int ph;

    if (size == 0 || p->recs != 0 || D_800B8C90() != 0) {
        return 0;
    }
    ret = 1;
    __asm__("" : "=r"(ret) : "0"(ret));
    ph = 4;
    __asm__("" : "=r"(ph) : "0"(ph));
    p->phase = ph;
    p->state = 1;
    p->start = func_8009F080;
    p->step = func_8009F128;
    n = (size + 3) >> 2 << 2;
    p->words = (unsigned short *)n;
    p->index = 0;
    n += (p->nwords + 1) >> 1 << 2;
    p->recs = (unsigned char *)n;
    p->ents = (CardEntry *)(n + ((p->nrecs * 5 + 3) & ~3));
    return ret;
}
