typedef struct {
    int id;
    int (*handler)(int, int);
} Driver;
typedef struct {
    char pad[8];
    Driver **start;
    Driver **end;
    unsigned int align;
} DriverList;
extern DriverList D_80086058;

int func_800868E0(int a, int b) {
    Driver **p;
    Driver **end;
    unsigned int mask;
    int ok;
    unsigned int align;

    ok = 1;
    align = D_80086058.align;
    mask = -align;
    p = (Driver **)((unsigned int)D_80086058.start & mask);
    end = (Driver **)((unsigned int)D_80086058.end & mask);
    for (; p < end; p = (Driver **)(((unsigned int)p + align) & mask)) {
        if ((*p)->handler != 0 && (*p)->handler(a, b) == -1) {
            ok = 0;
        }
    }
    return ok;
}
