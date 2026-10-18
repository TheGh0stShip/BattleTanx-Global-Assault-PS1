typedef struct PoolState {
    void *first;
    void *current;
    int pad;
    void *start;
    void *end;
    int active;
} PoolState;

extern PoolState D_800AD9EC;

void func_80068700(void) {
    D_800AD9EC.active = 0;
    D_800AD9EC.current = D_800AD9EC.first;
    D_800AD9EC.end = D_800AD9EC.start;
}
