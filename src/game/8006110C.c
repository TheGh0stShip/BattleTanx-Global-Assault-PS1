extern unsigned char D_800EAD64;
extern unsigned char D_800EADD0;
extern int func_8007A900(void *value);

int func_8006110C(int unused, unsigned char *object) {
    if (func_8007A900(*(void **)(object + 8)) & 1) {
        *(void **)(object + 0x28) = &D_800EAD64;
    } else {
        *(void **)(object + 0x28) = &D_800EADD0;
    }
    return 0;
}
