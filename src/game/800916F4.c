extern unsigned char D_800EEE3C[];

int func_800970D4(int first, int second);
void func_80091640();

void func_800916F4(void) {
    int result;

    if (D_800EEE3C[5] != 0) {
        do {
            result = func_800970D4(1, 0);
            if (result == 2 || result == 5) {
                func_80091640(result & 0xFF, 0);
            }
        } while (D_800EEE3C[5] != 0);
    }
}
