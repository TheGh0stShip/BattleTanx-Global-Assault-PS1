extern unsigned char D_800EEE3C[];

int func_80091604(void (*callback)(void));
void func_80091640();
int func_8009713C(int first, int second, int third);

void func_8009166C(void) {
    int count;
    int result;

    func_80091604(func_80091640);
    count = 0;
    do {
        D_800EEE3C[5] = 1;
        result = func_8009713C(9, 0, 0);
        count++;
    } while (count < 0x800 && result == 0);

    if (result == 0) {
        func_80091640(5, 0);
    }
}
