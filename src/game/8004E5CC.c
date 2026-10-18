void func_8004E2AC(void *object);
void func_80050454(void *object);

void func_8004E5CC(unsigned char *object) {
    if (*(unsigned int *)(object + 0x218) & 2) {
        func_8004E2AC(object);
    } else {
        *(unsigned int *)(object + 0x17C) = 0x1A;
        func_80050454(object);
    }
}
