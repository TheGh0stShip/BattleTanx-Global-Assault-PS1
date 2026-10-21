typedef struct {
    void (*func)(void *, int);
    void *param;
    int arg;
    unsigned long data[21];
} GpuQueueEntry;

typedef struct {
    unsigned char pad0;
    unsigned char sync_mode;
    unsigned char pad2[6];
    int pending;
    void (*callback)(void);
} GpuSyncState;

extern GpuSyncState D_800B0C60;
extern volatile unsigned long *D_800B0D38;
extern volatile unsigned long *D_800B0D44;
extern volatile int D_800B0D58;
extern volatile int D_800B0D5C;
extern int D_800B0D64;
extern volatile GpuQueueEntry D_800EC49C[];

extern int func_800944F4(int);
extern void func_80094450(int, void *);

int func_8008163C(void)
{
    if (*D_800B0D44 & 0x01000000)
        return 1;
    D_800B0D64 = func_800944F4(0);
    while (D_800B0D58 != D_800B0D5C && !(*D_800B0D44 & 0x01000000)) {
        if (((D_800B0D5C + 1) & 0x3F) == D_800B0D58 && D_800B0C60.callback == 0)
            func_80094450(2, 0);
        while (!(*D_800B0D38 & 0x04000000)) {
        }
        D_800EC49C[D_800B0D5C].func(D_800EC49C[D_800B0D5C].param, D_800EC49C[D_800B0D5C].arg);
        D_800B0D5C = (D_800B0D5C + 1) & 0x3F;
    }
    func_800944F4(D_800B0D64);
    if (D_800B0D58 == D_800B0D5C && !(*D_800B0D44 & 0x01000000)) {
        volatile GpuSyncState *st;
        void (*cb)(void);
        if (D_800B0C60.pending && (cb = D_800B0C60.callback) != 0) {
            st = &D_800B0C60;
            st->pending = 0;
            cb();
        }
    }
    return (D_800B0D58 - D_800B0D5C) & 0x3F;
}
