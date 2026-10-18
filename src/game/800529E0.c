typedef struct ActivationObject {
    unsigned char unused[0x5C];
    void *first;
    void *second;
    unsigned char active;
} ActivationObject;

extern void func_800149B8(void *first, void *second, int mode);

void func_800529E0(ActivationObject *object) {
    register ActivationObject *saved __asm__("$16") = object;

    if (!saved->active) {
        saved->active = 1;
        func_800149B8(saved->first, saved->second, 0);
    }
}
