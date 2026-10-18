extern void (*D_800EEE48)(void);

void func_800915AC(void) {
    if (D_800EEE48 != 0) {
        D_800EEE48();
    }
}
