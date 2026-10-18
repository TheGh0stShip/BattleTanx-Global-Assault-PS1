extern unsigned int D_800EEB34;

unsigned int func_80088B00(unsigned int first, unsigned int second) {
    unsigned int value = first + second;
    if (value >= D_800EEB34) {
        value -= D_800EEB34;
    }
    return value;
}
