typedef void (*CdlCB)(unsigned char, unsigned char *);

typedef struct {
    int time;
    int count;
    char *name;
} CdAlarm;

extern CdAlarm D_800EFCF0;
extern char D_800C5E84[];
extern char D_800C5E94[];
extern char D_800C5F0C[];
extern char *D_800B8D4C[];
extern char *D_800B8DCC[];
extern unsigned char D_800B8D45;
typedef struct {
    unsigned char sync;
    unsigned char ready;
    unsigned char c;
} CdIntr;

extern volatile CdIntr D_800B9004;
extern volatile unsigned char *D_800B8FEC;
extern CdlCB D_800B8D24;
extern CdlCB D_800B8D28;
extern unsigned char D_800EFCD8[8];
extern unsigned char D_800EFCE0[8];

extern int VSync(int mode);
extern int printf(const char *fmt, ...);
extern int puts_(const char *s);
extern void CD_flush(void);
extern int CheckCallback(void);
extern int CD_getintr(void);

static inline void cd_memcpy(void *dst, void *src, int size)
{
    unsigned char *d = dst;
    unsigned char *s = src;

    if (d == 0) {
        return;
    }
    while (size--) {
        *d++ = *s++;
    }
}

static inline int alarm_count(void)
{
    int c;
    int old;

    c = D_800EFCF0.count;
    old = c++;
    D_800EFCF0.count = c;
    return old;
}

static inline int get_alarm(void)
{
    if (D_800EFCF0.time < VSync(-1) || alarm_count() > 0x3C0000) {
        puts_(D_800C5E84);
        printf(D_800C5E94, D_800EFCF0.name, D_800B8D4C[D_800B8D45],
               D_800B8DCC[D_800B9004.sync], D_800B8DCC[D_800B9004.ready]);
        CD_flush();
        return -1;
    }
    return 0;
}

int func_8009FF30(int mode, unsigned char *result)
{
    int intr;
    unsigned char reg0;
    int sync;
    volatile unsigned char *ready;

    ready = &D_800B9004.ready;
    D_800EFCF0.time = VSync(-1) + 960;
    D_800EFCF0.count = 0;
    D_800EFCF0.name = D_800C5F0C;

    do {
        if (get_alarm()) {
            return -1;
        }
        if (CheckCallback()) {
            reg0 = *D_800B8FEC & 3;
            while ((intr = CD_getintr()) != 0) {
                if (intr & 4) {
                    if (D_800B8D28) {
                        D_800B8D28(*ready, D_800EFCE0);
                    }
                }
                if (intr & 2) {
                    if (D_800B8D24) {
                        D_800B8D24(D_800B9004.sync, D_800EFCD8);
                    }
                }
            }
            *D_800B8FEC = reg0;
        }
        sync = D_800B9004.sync;
        if (sync == 2 || sync == 5) {
            D_800B9004.sync = 2;
            cd_memcpy(result, D_800EFCD8, 8);
            return sync;
        }
    } while (mode == 0);
    return 0;
}
