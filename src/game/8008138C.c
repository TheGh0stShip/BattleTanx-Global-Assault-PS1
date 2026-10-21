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
extern int D_800B0D60;
extern volatile GpuQueueEntry D_800EC49C[];

extern void func_80081B28(void);
extern int func_80081B5C(void);
extern int func_8008163C(void);
extern int func_800944F4(int);
extern void func_80094450(int, void *);

int func_8008138C(void (*func)(void *, int), unsigned long *param, int len, int arg)
{
    int i;
    GpuSyncState *st;

    func_80081B28();
    while (((D_800B0D58 + 1) & 0x3F) == D_800B0D5C) {
        if (func_80081B5C()) {
            return -1;
        }
        func_8008163C();
    }
    D_800B0D60 = func_800944F4(0);
    st = &D_800B0C60;
    st->pending = 1;
    if (st->sync_mode == 0
        || (D_800B0D58 == D_800B0D5C && !(*D_800B0D44 & 0x01000000) && st->callback == 0)) {
        while (!(*D_800B0D38 & 0x04000000)) {
        }
        func(param, arg);
        func_800944F4(D_800B0D60);
        return 0;
    }
    func_80094450(2, func_8008163C);
    if (len != 0) {
        for (i = 0; i < len / 4; i++) {
            volatile unsigned long *dst = D_800EC49C[D_800B0D58].data;
            dst[i] = param[i];
        }
        D_800EC49C[D_800B0D58].param = D_800EC49C[D_800B0D58].data;
    } else {
        D_800EC49C[D_800B0D58].param = param;
    }
    D_800EC49C[D_800B0D58].arg = arg;
    D_800EC49C[D_800B0D58].func = func;
    D_800B0D58 = (D_800B0D58 + 1) & 0x3F;
    func_800944F4(D_800B0D60);
    func_8008163C();
    return (D_800B0D58 - D_800B0D5C) & 0x3F;
}
