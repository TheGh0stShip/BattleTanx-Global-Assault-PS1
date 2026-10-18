extern int D_800D2FE0;
extern struct {
    char pad[0x44];
    int deadline;
} D_800D2FE4;
extern int func_80022A08(int t);

int func_8006A820(void) {
    if (func_80022A08(D_800D2FE4.deadline) > D_800D2FE0) {
        return (func_80022A08(D_800D2FE4.deadline) - D_800D2FE0 + 59) / 60 * 100;
    }
    return 0;
}
