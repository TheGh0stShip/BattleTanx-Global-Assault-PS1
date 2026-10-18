unsigned int func_80085848(void *first, void *second);
unsigned int func_80085DB0(void *first, void *second);
void func_80085DD4(void *value);
unsigned int func_80085EB4(void *value);

unsigned int func_80085FAC(unsigned int operation, void *first, ...) {
    register unsigned int result asm("$16") = 0;
    register void *original_first asm("$5") = first;
    register void *first_copy asm("$3") = original_first;
    register unsigned char *stack asm("$29");

    asm("" : "+r"(first_copy));
    *(void **)(stack + 28) = original_first;
    switch (operation) {
    case 0:
        result = func_80085848(first_copy, *(void **)(stack + 32));
        break;
    case 1:
        result = func_80085DB0(*(void **)(stack + 32),
                               *(void **)(stack + 36));
        break;
    case 2:
        func_80085DD4(*(void **)(stack + 32));
        break;
    case 3:
        result = func_80085EB4(first_copy);
        break;
    }
    return result;
}
