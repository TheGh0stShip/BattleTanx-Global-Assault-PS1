extern int func_800973AC(int, int, unsigned char *);
extern void func_80088870(int);

int func_8009B04C(int mode) {
    unsigned char result[8];
    int ret;
    int i;

    func_800973AC(1, 0, result);
    if (result[0] & 0x10) {
        return 16;
    }
    ret = func_800973AC(19, 0, result);
    if (mode == 1) {
        if (result[0] == 2 && ret != 0) {
            return 2;
        }
        return 5;
    }
    for (i = 0; i < 10; i++) {
        if (result[0] & 2) {
            while (result[0] != 2 || ret == 0) {
                func_80088870(30);
                ret = func_800973AC(19, 0, result);
            }
            return 2;
        }
        func_80088870(30);
        ret = func_800973AC(19, 0, result);
    }
    return 5;
}
