void func_80050AAC(unsigned char *object);
void func_80048F2C(unsigned char *object, int value);
void func_80050AE0(unsigned char *object, int value);

void func_80050024(unsigned char *object, int value) {
    if (*(int *)(object + 0x94) != 0) {
        func_80050AAC(object);
        func_80048F2C(object, value);
        func_80050AE0(object, value);
    }
}
