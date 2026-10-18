typedef int (*RuntimeProbe)(void *handle, int first, int second, int third);

extern unsigned char D_800EDC9C;
extern void *func_80082BEC(void *handle, int first, int second, int third);
extern void func_80083194(void *handle);
extern int func_8008314C(void *handle, int value);

void *func_80082798(void *handle, int first, int second)
{
    unsigned char *runtime;
    void *result;
    int released;

    result = func_80082BEC(handle, first, second, 0);
    released = 0;
    if (result != 0) {
        runtime = &D_800EDC9C;
        do {
            RuntimeProbe probe = *(RuntimeProbe *)(runtime + 0x268);
            if (probe != 0 && probe(handle, 0, 0, 0) == 0) {
                func_80083194(handle);
                released = 1;
            }
            if (func_8008314C(handle, 0) != 0) {
                break;
            }
        } while (released == 0);
    }

    return result;
}
