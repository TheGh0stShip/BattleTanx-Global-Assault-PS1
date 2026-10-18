extern void func_8006F224(void *object, void *value);

void func_80071320(unsigned char *object) {
    func_8006F224(*(void **)(object + 8), 0);
    func_8006F224(*(void **)(object + 12), 0);
    object[0x14] = 1;
}
