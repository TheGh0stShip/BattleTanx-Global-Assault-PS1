extern int D_800ADD04;
extern int D_800E53F0;
extern int func_80085848(int value, void *argument);
extern int func_80085F5C(int value);

int func_80068FC8(void *argument) {
    int result;

    D_800ADD04++;
    D_800E53F0 = func_80085F5C(-1);
    result = func_80085848(-1, argument);
    if ((unsigned int)result <= 0xEA5F) {
        for (;;) {
        }
    }
    return result;
}
