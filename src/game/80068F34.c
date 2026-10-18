extern int D_800ADD08;
extern int D_800E53F0;
extern int func_80085F5C(int value);
extern int func_80085870(int value, void *argument);

int func_80068F34(void *argument) {
    int result;

    D_800ADD08++;
    D_800E53F0 = func_80085F5C(-1);
    result = func_80085870(-1, argument);
    if ((unsigned int)result <= 0xEA5F) {
        for (;;) {
        }
    }
    return result;
}
