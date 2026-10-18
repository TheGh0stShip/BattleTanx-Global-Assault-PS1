extern void func_80082424(void *descriptor, void *source);
extern void *func_80068DA4(void *resource);
extern void func_80082854(void *descriptor, void *result, void *resource);
extern void func_800826A0(void *descriptor);

void *func_8003DCAC(void *source) {
    unsigned char descriptor[72];
    void *resource;
    void *result;

    func_80082424(descriptor, source);
    resource = *(void **)(descriptor + 12);
    result = func_80068DA4(resource);
    func_80082854(descriptor, result, resource);
    func_800826A0(descriptor);
    return result;
}
