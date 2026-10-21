extern void *D_800B8D24;
extern unsigned char D_800B8D34;
extern int D_800B6C94[];
extern int func_800A0478(int command, unsigned char *param, unsigned char *result, int async);

int func_80097278(unsigned char command, unsigned char *param) {
    void *savedCallback = D_800B8D24;
    int tries = 4;
    int failed;

    while (tries-- != 0) {
        D_800B8D24 = 0;
        failed = 0;
        if (command != 1 && (D_800B8D34 & 0x10)) {
            func_800A0478(1, 0, 0, 0);
        }
        if (param == 0 || D_800B6C94[command] == 0 || func_800A0478(2, param, 0, 0) == 0) {
            D_800B8D24 = savedCallback;
            if (func_800A0478(command, param, 0, 1) == 0) {
                goto done;
            }
        }
    }
    D_800B8D24 = savedCallback;
    failed = -1;
done:
    return failed + 1;
}
